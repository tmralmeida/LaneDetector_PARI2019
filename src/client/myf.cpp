/**
 * @file myf.cpp
 * @author Tiago Almeida, nº 77107 (tm.almeida@ua.pt)
 * @brief File theat includes the sections of Child and Parent and Image Segmentation Parts. 
 * @Final Version
 * @date 2019-01-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "myclient.h"
#include "myutils.h"

/**
 * @brief Highlight the Message from Child
 * @param  str- The string that is going to be highlighted
 * @return 
 */

void MessageFromChild(char *str)
{
    textcolor1(RESET, RED, WHITE); //from pcolor
    printf("\nMessage From Child: %s", str);
    ResetTextColors1(); //from pcolor
}

/**
 * @brief Highlight the Message from Parent
 * @param  str- The string that is going to be highlighted
 * @return 
 */

void MessageFromParent(char *str)
{
    textcolor1(RESET, GREEN, WHITE); //from pcolor
    printf("\nMessage From Parent: %s", str);
    ResetTextColors1(); //from pcolor
}

/**
 * @brief The functionn that provides the chuild control under the GTK interface.
 * @param  
 * @return an integer
 */

int ChildMain3(int argc, char *argv[])
{

    int n, shm_id;
    char *gladeFile = (char *)"Project.glade";
    int ret;
    shm_id = GetSharedMem();
    if (shm_id == -1)
        return -1; //failure

    /* attach to the memory segment to get a pointer to it */
    //data = (char *)shmat(shm_id, (void *)0, 0);
    data = (struct Memory *)shmat(shm_id, NULL, 0);
    if (data == (struct Memory *)(-1))
    {
        perror("shmat");
        exit(1);
    }
    strcpy(data->data_filho, " ");

    gtk_init(&argc, &argv);
    /*Create a new gtk builder to contain a GUI */
    builderG = gtk_builder_new();
    /* load the interface from a file */
    ret = gtk_builder_add_from_file(builderG, gladeFile, NULL);

    if (!ret)
    {
        g_print("%s file was not found. Aborting!\n", gladeFile);
        return 0;
    }
    //g_timeout_add(30, (GSourceFunc) pari_UpdateMyDisplay, (gpointer) NULL);
    /* connect the signals in the interface */
    gtk_builder_connect_signals(builderG, NULL);

    /* get main window ID after window name in the glade file! */
    /* This is necessary because names must be read from the user GUI file */
    GtkWidget *t = GTK_WIDGET(gtk_builder_get_object(builderG, "MainWindow"));
    //gtk_window_unmaximize ("MainWindow");

    // use signal to catch SIGINT  (CTRL-C)
    signal((int)SIGINT, (sighandler_t)InterceptCTRL_C);

    g_timeout_add(30, (GSourceFunc)pari_UpdateMyDisplay, (gpointer)NULL);

    /* start the event loop */
    gtk_main();

    cvReleaseImage(&dst_imageG); //Release image (free pointer when no longer used)
    cvReleaseImage(&src_imageG); //Release image (free pointer when no longer used).

    puts("Fechei a interface gráfica e vou-me embora!");

    /* detach from the mem segment */
    if (shmdt((void *)data) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    return 0;
}

/**
 * @brief The functionn that provides the parent control under the comunications between the server and the client.
 * @param  
 * @return an integer
 */

using namespace cv;
using namespace std;
int ParentMain3(int argc, char *argv[])
{
    int socket_desc;
    int ret;
    struct hostent *serverByname;
    struct sockaddr_in server;
    char message[120] = {0};
    char server_reply[MAXCHARS] = {0}; //an emptied buffer for server reply
    char ip[16] = "127.0.0.1";         //this is lars.mec.ua.pt. Can use others.
    int port = 50000;
    int n, shm_id;
    char str[60];      //string to put a message
    struct timeval tt; //aux variable to read system time
    //-------------------------------------------------------------------//
    //Variáveis relativas à imagem:
    int bytes_lidos = 0; //contador de bytes lidos na imagem
    int num_channels = 3;
    int chunk_falta;       //se existir algum chunk a faltar-debugger
    int data_received = 0; //variável que guarda quantos bytes chegam de cada vez an receção da imagem
    int ptr = 0;           //entra no ciclo que compoe a imagem segundo os pixels
    int i, ii, j;          //variaveis que entram nos ciclos 'for'
    int imgSize = 0;
    int dim_recv = 0;
    char str_size[50] = {0};
    char *p = {0};
    char *vals_dims[2] = {0};
    int tss = 0;

    shm_id = GetSharedMem();
    if (shm_id == -1)
        return -1; //failure

    /* attach to the memory segment to get a pointer to it */
    data = (struct Memory *)shmat(shm_id, NULL, 0);
    if (data == (struct Memory *)(-1))
    {
        perror("shmat");
        exit(1);
    }
    //printf("Mensagem Inicial para o Servidor:%s\n", message);
    data->pedid_ligacao = 0;
    data->status = 0;
    data->exist_ligacao = 0;
    bzero(data->data_pai_imgdata, 3932170);
    do
    {
        //fill server details
        if (argc > 2)
            port = atoi(argv[2]); // if two arguments, the second is the port
        if (argc > 1)
        {
            serverByname = gethostbyname(argv[1]);
            if (serverByname == NULL)
            {
                fprintf(stderr, "ERROR, no such host %s\n", argv[1]);
                return 1;
            }
            bcopy(serverByname->h_addr, &server.sin_addr.s_addr, serverByname->h_length); //copy bytes
        }
        else
            server.sin_addr.s_addr = inet_addr(ip);

        //printf("\nExiste Ligacao? %d\n", data->pedid_ligacao);
        if (data->pedid_ligacao == 1)
        {
            //printf("INICIOIF::Estado  do lado do if-pedid_ligacao:%d\n", data->pedid_ligacao);
            //printf("INICIOIF:::Estado  do lado do if-status?:%d\n", data->status);
            //printf("INICIOIF:::Estado  do lado do if-existe ligacao?:%d\n", data->exist_ligacao);

            socket_desc = socket(AF_INET, SOCK_STREAM, 0);

            if (socket_desc == -1)
                printf("Could not create socket");

            server.sin_family = AF_INET;
            server.sin_port = htons(port);

            //Connect to remote server using the created socket
            ret = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
            if (ret < 0)
            {
                puts("connect error");
                return 1;
            }

            puts("Everything OK with the connection");

            //Enviar mensagem da connection

            strcpy(message, data->data_filho);
            //printf("\nMessagem Inicial (Cliente-Servidor)=%s\n", message);
            ret = send(socket_desc, message, strlen(message), 0);
            if (ret < 0)
            {
                puts("Send failed");
                return 1;
            }
            puts("\nMensagem enviada com sucesso!\n");
            bzero(server_reply, MAXCHARS); //important when reading repeatidely
            ret = recv(socket_desc, server_reply, MAXCHARS, 0);

            if (ret < 0)
            {
                printf("recv failed\n");
            }
            PrintRedLine1();
            printf("---------Resposta do Servidor: %s", server_reply);
            ResetTextColors1();
            sprintf(data->data_pai, "Parent message %s to my son", server_reply);
            sprintf(str, "  %s\n", data->data_pai);

            //----------------------------------------------------//
            data->pedid_ligacao = 0;
            data->status = 0;
            data->exist_ligacao = 1;
            //printf("FIMIF::Estado  do lado do if-pedid_ligacao:%d\n", data->pedid_ligacao);
            //printf("FIMIF:::Estado  do lado do if-status?:%d\n", data->status);
            //printf("FIMlIF:::Estado  do lado do if-existe ligacao?:%d\n", data->exist_ligacao);
            usleep(1000000);
        }
        //printf("\nEstado  do lado do myf-pedid_ligacao:%d\n", data->pedid_ligacao);
        //printf("\nEstado  do lado do myf-status?:%d\n", data->status);
        //printf("\nEstado  do lado do myf-existe ligacao?:%d\n", data->exist_ligacao);
        usleep(1000000);
        while (data->exist_ligacao)
        {
            //printf("-Estado  antes do if:%d\n", data->status);
            usleep(1000000);
            if (data->status == 1)
            {
                //printf("--Estado  depois do if:%d\n", data->status);
                usleep(1000000);
                strcpy(message, data->data_filho);
                //printf("\nOutras Mensagens (Cliente-Servidor)=%s\n", message);
                ret = send(socket_desc, message, strlen(message), 0);
                if (ret < 0)
                {
                    puts("Send failed");
                    return 1;
                }
                puts("\nMensagem enviada com sucesso!\n");
                bzero(server_reply, MAXCHARS); //important when reading repeatidely

                if ((strncmp(message, "mais uma imagem", sizeof("mais uma imagem")) == 0) || (strncmp(message, "imagem anterior", sizeof("imagem anterior")) == 0))
                {
                    //Receiving the header with the dimensions:
                    str_size[50] = {0};
                    vals_dims[2] = {0};
                    p = {0};
                    data->height = 0;
                    data->width = 0;
                    tss = 0;
                    //int tss=0;

                    dim_recv = recv(socket_desc, str_size, 50, 0);
                    if (dim_recv < 0)
                    {
                        puts("Send failed");
                        return 1;
                    }
                    //printf("Tamanho da Imagem recebida:%s\n", str_size);
                    p = strtok(str_size, ",");

                    while (p != NULL)
                    {
                        vals_dims[tss++] = p;
                        p = strtok(NULL, ",");
                    }
                    /*
                    for (tss = 0; tss < 2; ++tss)
                    {
                        printf("VALS_DIMS:ERRROOOOOOO-%s\n", vals_dims[tss]);
                    }*/
                    //printf("Width=%s\n", vals_dims[0]);
                    //printf("Height=%s\n", vals_dims[1]);
                    data->width = atoi(vals_dims[0]);
                    data->height = atoi(vals_dims[1]);
                    bzero(str_size, 50);
                    bzero(vals_dims, 2);

                    //-----------------------------------------------//
                    ret = send(socket_desc, "agora manda-me a imagem", strlen("agora manda-me a imagem"), 0);
                    if (ret < 0)
                    {
                        puts("Send failed");
                        return 1;
                    }
                    imgSize = data->width * data->height * num_channels;
                    uchar sockData[imgSize]; //Buffer onde sera guardada a imagem
                    bzero(sockData, imgSize);
                    //printf("Tamanho da Imagem:%d\n", imgSize);
                    //Receive data here:
                    for (i = 0; i < imgSize; i += data_received)
                    {
                        if ((data_received = recv(socket_desc, sockData + i, imgSize - i, 0)) == -1)
                        {
                            printf("recv failed\n");
                        }
                        bytes_lidos += data_received;
                        /*
                        if (data_received != 0)
                        {
                            printf("\nTamanho dos chunks recebidos:%d\n", data_received);
                        }*/
                    }
                    chunk_falta = imgSize - i;

                    //printf("\nTamanho do pacote total lido: %d", bytes_lidos);
                    //printf("\nTamanho do chunk que falta: %d", chunk_falta);//Debugger
                    memcpy(&data->data_pai_imgdata, sockData, imgSize);
                    bzero(sockData, imgSize);
                    usleep(500000);
                }
                //--------------------------------------------------------------------------------------------//
                //Comunicação com strings:
                else
                {
                    ret = recv(socket_desc, server_reply, MAXCHARS, 0);
                    if (ret < 0)
                    {
                        printf("recv failed\n");
                    }
                    //PrintRedLine1();
                    //printf("---------Resposta do Servidor: %s\n", server_reply);
                    //ResetTextColors1();
                    sprintf(data->data_pai, "Parent message %s to my son", server_reply);
                    sprintf(str, "  %s\n", data->data_pai);
                    MessageFromParent(str);
                }

                data->status = 0;
            }
        }

        close(socket_desc);
    } while (strncmp(message, "quit", 4) != 0);

    //MessageFromParent(str);
    if (shmdt(data) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    //close the socket before exiting

    return shm_id;
}

/**
 * @brief  Gets a shared memory and connects to it
 *
 * The function first creates a random key to identify
 * the memory and then connects to it with some specific permissions
 * @return int The Shared memory ID. Returns -1 in case of failure.
 */

int GetSharedMem()
{
    key_t key; /*it's a long int */
    int shm_id;
    key = ftok("/", 'X'); /* generate a random key based on a file name and char */
    if (key == -1)
    {
        perror("ftok");
        return -1;
    }

    /* now connect to (or possibly create) the shared memory segment with permission 644 */
    //shm_id = shmget(key, SHM_SIZE, 0644 | IPC_CREAT);
    shm_id = shmget(key, sizeof(struct Memory), 0644 | IPC_CREAT);
    if (shm_id == -1)
    {
        perror("shmget");
        return -1;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//
//Image Processing Section

/**
 * @brief  Function that creates the images from the SH, that will show up on the interface
 *
 *      
 *
 */

void pari_PerformImageAcquisition()
{
    int ii;
    int j;
    Mat img;
    if ((data->width != 0) && (data->height != 0))
    {
        img = Mat::zeros(data->height, data->width, CV_8UC3);
    }
    else
    {
        img = Mat::zeros(600, 500, CV_8UC3);
    }

    int imgSize = img.total() * img.elemSize();
    int ptr = 0;

    for (ii = 0; ii < img.rows; ii++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.at<cv::Vec3b>(ii, j) = cv::Vec3b(data->data_pai_imgdata[ptr + 0], data->data_pai_imgdata[ptr + 1], data->data_pai_imgdata[ptr + 2]);
            ptr = ptr + 3;
        }
    }
    //data->height=0;
    //data->width=0;
    IplImage *image2;
    image2 = cvCreateImage(cvSize(img.cols, img.rows), 8, 3);
    IplImage ipltemp = img;
    cvCopy(&ipltemp, image2);
    cvCvtColor(image2, image2, CV_BGR2RGB);

    if (src_imageG)
    {
        cvReleaseImage(&src_imageG);
    }
    if (dst_imageG)
    {
        cvReleaseImage(&dst_imageG);
    }
    src_imageG = cvCloneImage(image2);
    dst_imageG = cvCloneImage(src_imageG);
    cvReleaseImage(&image2);
    img.release();
}

/**
 * @brief  Function that converts an IplImage into a pixbuf for display purposes
 *
 * @param  image The IplImage
 * @param  dst_w width of the new pixbuf
 * @param  dst_h height of the new pixbuf
 * @return The GdkPixbuf 
 */

GdkPixbuf *pari_ConvertOpenCv2Gtk(IplImage *image, int dst_w, int dst_h)
{
    IplImage *gtkMask = image;
    GdkPixbuf *pix, *rpix;
    pix = gdk_pixbuf_new_from_data((guchar *)gtkMask->imageData,
                                   GDK_COLORSPACE_RGB,
                                   FALSE,
                                   gtkMask->depth,
                                   gtkMask->width,
                                   gtkMask->height,
                                   gtkMask->widthStep,
                                   NULL, //callback to free allocated memory: void (*GdkPixbufDestroyNotify) (guchar *pixels, gpointer fn_data);
                                   NULL  //argument to previous callback: gpointer fn_data
    );

    rpix = gdk_pixbuf_scale_simple(pix, dst_w, dst_h, GDK_INTERP_BILINEAR);
    g_object_unref(pix); //free the intermediate pixbuf...
    return rpix;
}

/**
 * @brief Copy from Iplimage to pixbuf and paint the widget
 *
 * @param  widgetName String with the widget name in glade
 * @param  img IplImage where to get the image from
 * @return void
 */
void pari_RefreshDrawingArea(char *widgetName, IplImage *img)
{
    GtkWidget *da = GTK_WIDGET(gtk_builder_get_object(builderG, widgetName));
    if (!da)
    {
        printf("failed for %s\n", widgetName);
        return;
    }

    int wd = gtk_widget_get_allocated_width(da);  //also img->width for full size always
    int ht = gtk_widget_get_allocated_height(da); //also img->height for full size always

    GdkPixbuf *pix = pari_ConvertOpenCv2Gtk(img, wd, ht);
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(da));
    gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
    cairo_paint(cr);
    cairo_fill(cr);
    cairo_destroy(cr);
    g_object_unref(pix); //free the pixbuf ... not sure if it works as expected
}

/**
 * @brief  Function to perform all of the image operations 
 *
 * @param  src Source image to process
 * @param  dst Image to put the processed result
 * @param  gb  GtkBuilder pointer for the currently loaded GUI.
 */
void pari_ProcessUserOperations(IplImage *src, IplImage *dst)
{
    cvCopy(src, dst, NULL); //copiar a imagem para dst
    UserOperationBinarization(src, dst, builderG, (gpointer) "check_binarizacao", (gpointer) "adjustment_binarizacao");
    UserOperationCanny(src, dst, builderG, (gpointer) "check_filtros", (gpointer) "adjustment_canny");
    UserOperationHSV(src, dst, builderG, (gpointer) "check_canais", (gpointer) "adjustment_Hmin", (gpointer) "adjustment_Hmax", (gpointer) "adjustment_Smin", (gpointer) "adjustment_Smax", (gpointer) "adjustment_Vmin", (gpointer) "adjustment_Vmax");
    UserOperationRotation(dst, dst, builderG, (gpointer) "check_rotacao", (gpointer) "adjustment_angle");
}

/**
 * @brief  Function to perform some specific operation. Threshold!
 *
 * @param  src Source image to process
 * @param  dst Image to put the processed result
 * @param  check_binarizacao the toggle button that user can click on it
 * @param  adjustment_binarizacao is the adjustment that returns the value of the trackbar 
 */

void UserOperationBinarization(IplImage *src, IplImage *dst, GtkBuilder *gb, gpointer check_binarizacao, gpointer adjustment_binarizacao)
{
    IplImage *tmp_gray = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1); //aux image
    if (!(gb && check_binarizacao && adjustment_binarizacao))
        return;

    GtkToggleButton *binon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)check_binarizacao));
    GtkAdjustment *bin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_binarizacao));
    gboolean binOn = gtk_toggle_button_get_active(binon_w);
    gdouble binLim = gtk_adjustment_get_value(bin_adj);

    if (binOn == 1)
    {
        cvCvtColor(src, tmp_gray, CV_RGB2GRAY);
        cvThreshold(tmp_gray, tmp_gray, binLim, 255, CV_THRESH_BINARY);
        cvMerge(tmp_gray, tmp_gray, tmp_gray, NULL, dst);
    }
    cvReleaseImage(&tmp_gray);
}

/**
 * @brief  Function to perform some specific operation. Canny Filter!
 *
 * @param  src Source image to process
 * @param  dst Image to put the processed result
 * @param  check_filtros the toggle button that user can click on it
 * @param  adjustment_binarizacao is the adjustment that returns the value of the trackbar threshold for canny filter
 */

void UserOperationCanny(IplImage *src, IplImage *dst, GtkBuilder *gb, gpointer check_filtros, gpointer adjustment_canny)
{
    IplImage *tmp_gray = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1); //aux image
    if (!(gb && check_filtros && adjustment_canny))
    {
        return;
    }
    GtkToggleButton *checkon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)check_filtros));
    GtkAdjustment *bin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_canny));
    gboolean checkOn = gtk_toggle_button_get_active(checkon_w);
    gdouble binLim = gtk_adjustment_get_value(bin_adj);

    if (checkOn == 1)
    {
        cvCvtColor(src, tmp_gray, CV_RGB2GRAY);
        cvCanny(tmp_gray, tmp_gray, 0, binLim, 3); //muda o threshold
        cvMerge(tmp_gray, tmp_gray, tmp_gray, NULL, dst);
    }
    cvReleaseImage(&tmp_gray);
}

/**
 * @brief  Function to perform some specific operation. Changing the HSV colorspace!
 *
 * @param  src Source image to process
 * @param  dst Image to put the processed result
 * @param  check_canais the toggle button that user can click on it
 * @param  all of the adjustments that return the value of the trackbar value for all the image channels 
 */

void UserOperationHSV(IplImage *src, IplImage *dst, GtkBuilder *gb, gpointer check_canais, gpointer adjustment_Hmin, gpointer adjustment_Hmax, gpointer adjustment_Smin, gpointer adjustment_Smax, gpointer adjustment_Vmin, gpointer adjustment_Vmax)
{
    IplImage *tmp_HSV = cvCreateImage(cvGetSize(src), 8, 3);
    IplImage *imgThreshed = cvCreateImage(cvGetSize(src), 8, 1);

    if (!(gb && check_canais && adjustment_Hmin && adjustment_Hmax && adjustment_Smin && adjustment_Smax && adjustment_Vmin && adjustment_Vmax))
        return;
    GtkToggleButton *canon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)check_canais));
    GtkAdjustment *Hmin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_Hmin));
    GtkAdjustment *Smin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_Smin));
    GtkAdjustment *Vmin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_Vmin));
    GtkAdjustment *Hmax_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_Hmax));
    GtkAdjustment *Smax_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_Smax));
    GtkAdjustment *Vmax_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_Vmax));
    gboolean canOn = gtk_toggle_button_get_active(canon_w);
    gdouble HLimmin = gtk_adjustment_get_value(Hmin_adj);
    gdouble SLimmin = gtk_adjustment_get_value(Smin_adj);
    gdouble VLimmin = gtk_adjustment_get_value(Vmin_adj);
    gdouble HLimmax = gtk_adjustment_get_value(Hmax_adj);
    gdouble SLimmax = gtk_adjustment_get_value(Smax_adj);
    gdouble VLimmax = gtk_adjustment_get_value(Vmax_adj);

    if (canOn)
    {
        cvCvtColor(src, tmp_HSV, CV_RGB2HSV);
        cvInRangeS(tmp_HSV, cvScalar(HLimmin, SLimmin, VLimmin), cvScalar(HLimmax, SLimmax, VLimmax), imgThreshed);
        cvMerge(imgThreshed, imgThreshed, imgThreshed, NULL, dst);
    }
    cvReleaseImage(&tmp_HSV);
    cvReleaseImage(&imgThreshed);
}

/**
 * @brief  Function to perform some specific operation. Image Rotation!
 *
 * @param  src Source image to process
 * @param  dst Image to put the processed result
 * @param  check_rotacao the toggle button that user can click on it
 * @param  adjustment_angle is the adjustment that returns the value of the trackbar angle value 
 */

void UserOperationRotation(IplImage *src, IplImage *dst, GtkBuilder *gb, gpointer check_rotacao, gpointer adjustment_angle)
{
    double ang;
    CvPoint2D32f center; //variável do tipo Point2D em vírgula flutuante
    if (!(gb && check_rotacao && adjustment_angle))
        return;

    GtkToggleButton *roton_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)check_rotacao));
    GtkAdjustment *rot_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)adjustment_angle));
    gboolean rotOn = gtk_toggle_button_get_active(roton_w);
    gdouble rotLim = gtk_adjustment_get_value(rot_adj);

    if (rotOn)
    {
        center.x = src->width / 2;                          //x do centro da imagem
        center.y = src->height / 2;                         //y do centro da imagem
        CvMat *mapMatrix = cvCreateMat(2, 3, CV_32FC1);     //alocação de espaço para uma matriz de 2X3 (ver manual)
        cv2DRotationMatrix(center, rotLim, 1.0, mapMatrix); //preenchimento da matriz com os valores adequados à rotação
                                                            //Aplicação da matriz na imagem src e escrita em dest e parâmetros de interpolação
        cvWarpAffine(src, dst, mapMatrix,
                     CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS,
                     cvScalarAll(0));
        cvReleaseMat(&mapMatrix); // libertação do espaço alocado para a matriz
    }
}
