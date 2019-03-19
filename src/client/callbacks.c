/**
 * @file callbacks.c
 * @author Tiago Almeida, nº 77107 (tm.almeida@ua.pt)
 * @brief File that includes all of the callbacks that are associated with the GTK interface
 * @Final Version
 * @date 2019-01-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "myclient.h"

/**
 * @brief  Function that makes the help window shows.
 *
 * @param  the widget 
 */

void on_Button_Ajuda_clicked()
{

    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "messagedialog1"));
    //GtkWidget *main_window=GTK_WIDGET(gtk_builder_get_object(builderG, "MainWindow"));
    //gtk_window_set_transient_for(w,main_window);
    gtk_widget_show(w);
}

/**
 * @brief  Function that makes the Threshold value window Shows.
 *
 * @param  the widget 
 */

void on_check_binarizacao_toggled()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "binarization_Window"));
    GtkToggleButton *binon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_binarizacao"));
    GtkToggleButton *checkon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_filtros"));
    GtkToggleButton *channelon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_canais"));
    GtkToggleButton *valrecon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recomendados"));
    GtkToggleButton *recbin_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recbin"));
    GtkToggleButton *reccan_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_reccann"));
    gboolean binOn = gtk_toggle_button_get_active(binon_w);
    if (binOn == 1)
    {
        gtk_toggle_button_set_active(checkon_w, 0);
        gtk_toggle_button_set_active(channelon_w, 0);
        gtk_toggle_button_set_active(valrecon_w, 0);
        gtk_toggle_button_set_active(reccan_w, 0);
        gtk_widget_show(w);
    }
    else
    {
        gtk_toggle_button_set_active(recbin_w, 0);
    }
}

/**
 * @brief  Function that makes the Canny Threshold Value window shows.
 *
 * @param  the widget 
 */

void on_check_filtros_toggled()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "binarization_Window1"));
    GtkToggleButton *binon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_binarizacao"));
    GtkToggleButton *checkon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_filtros"));
    GtkToggleButton *channelon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_canais"));
    GtkToggleButton *valrecon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recomendados"));
    GtkToggleButton *reccan_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_reccann"));
    GtkToggleButton *recbin_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recbin"));
    gboolean checkOn = gtk_toggle_button_get_active(checkon_w);
    if (checkOn == 1)
    {
        gtk_toggle_button_set_active(binon_w, 0);
        gtk_toggle_button_set_active(channelon_w, 0);
        gtk_toggle_button_set_active(valrecon_w, 0);
        gtk_toggle_button_set_active(recbin_w, 0);
        gtk_widget_show(w);
    }
    else
    {
        gtk_toggle_button_set_active(reccan_w, 0);
    }
}

/**
 * @brief  Function that makes the Rotation Image window shows.
 *
 * @param  the widget 
 */

void on_check_rotacao_toggled()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "rotation_Window"));
    GtkToggleButton *roton_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_rotacao"));
    gboolean checkOn = gtk_toggle_button_get_active(roton_w);
    if (checkOn == 1)
    {
        gtk_widget_show(w);
    }
    else
    {
        gtk_widget_hide(w);
    }
}

/**
 * @brief  Function that makes the HSV channels values window shows.
 *
 * @param  the widget 
 */

void on_check_canais_toggled()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "HSV_Window"));
    GtkToggleButton *binon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_binarizacao"));
    GtkToggleButton *checkon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_filtros"));
    GtkToggleButton *channelon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_canais"));
    GtkToggleButton *valrecon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recomendados"));
    GtkToggleButton *reccan_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_reccann"));
    GtkToggleButton *recbin_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recbin"));

    gboolean channelkOn = gtk_toggle_button_get_active(channelon_w);
    if (channelkOn == 1)
    {
        gtk_toggle_button_set_active(binon_w, 0);
        gtk_toggle_button_set_active(checkon_w, 0);
        gtk_toggle_button_set_active(reccan_w, 0);
        gtk_toggle_button_set_active(recbin_w, 0);
        gtk_widget_show(w);
    }
    else
    {
        gtk_toggle_button_set_active(valrecon_w, 0);
    }
}

/**
 * @brief  Function that makes the threshold value recommended window shows
 *
 * @param  the widget 
 */

void on_check_recbin_toggled()
{

    GtkToggleButton *binon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_binarizacao"));
    GtkToggleButton *recbin_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recbin"));

    gtk_toggle_button_set_active(binon_w, 0);
    gboolean recbinOn = gtk_toggle_button_get_active(recbin_w);

    GtkAdjustment *bin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_binarizacao"));
    gdouble thresh;

    if (recbinOn == 1)
    {
        if (count_images == 1)
        {
            thresh = 249;
        }
        else if (count_images == 2)
        {
            thresh = 238;
        }
        else if ((count_images == 3) || (count_images == 4))
        {
            thresh = 154;
        }
        else if (count_images == 5)
        {
            thresh = 192;
        }
        else if (count_images == 6)
        {
            thresh = 143;
        }
        else if (count_images == 7)
        {
            thresh = 214;
        }
        else if (count_images == 8)
        {
            thresh = 194;
        }
        else if (count_images == 9)
        {
            thresh = 184;
        }
        else if (count_images >= 10)
        {
            thresh = 176;
        }
        gtk_adjustment_set_value(bin_adj, thresh);
        gtk_toggle_button_set_active(binon_w, 1);
    }
}

/**
 * @brief  Function that makes the threshold canny recommended window shows  
 *
 * @param  the widget 
 */

void on_check_reccann_toggled()
{
    GtkToggleButton *filton_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_filtros"));
    GtkToggleButton *reccan_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_reccann"));

    gtk_toggle_button_set_active(filton_w, 0);
    gboolean recbinOn = gtk_toggle_button_get_active(reccan_w);

    GtkAdjustment *canny_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_canny"));
    gdouble thresh_canny = 255;

    if (recbinOn == 1)
    {
        gtk_adjustment_set_value(canny_adj, thresh_canny);
        gtk_toggle_button_set_active(filton_w, 1);
    }
}

/**
 * @brief  Function that makes the HSV channels values window shows but in order to turn better the rcommended values 
 *
 * @param  the widget 
 */

void on_check_recomendados_toggled()
{
    GtkToggleButton *channelon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_canais"));
    GtkToggleButton *valrecon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recomendados"));
    gtk_toggle_button_set_active(channelon_w, 0);
    gboolean valrecOn = gtk_toggle_button_get_active(valrecon_w);

    GtkAdjustment *Hmin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_Hmin"));
    GtkAdjustment *Smin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_Smin"));
    GtkAdjustment *Vmin_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_Vmin"));
    GtkAdjustment *Hmax_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_Hmax"));
    GtkAdjustment *Smax_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_Smax"));
    GtkAdjustment *Vmax_adj = GTK_ADJUSTMENT(gtk_builder_get_object(builderG, (const gchar *)"adjustment_Vmax"));

    gdouble HLimmin;
    gdouble HLimmax;
    gdouble SLimmin;
    gdouble SLimmax;
    gdouble VLimmin;
    gdouble VLimmax;

    if (valrecOn == 1)
    {
        if (count_images == 1)
        {
            HLimmin = 0;
            HLimmax = 0;
            SLimmin = 0;
            SLimmax = 0;
            VLimmin = 0;
            VLimmax = 255;
        }
        else if (count_images == 2)
        {
            HLimmin = 0;
            HLimmax = 58;
            SLimmin = 0;
            SLimmax = 67.9;
            VLimmin = 255;
            VLimmax = 255;
        }
        else if (count_images == 4)
        {
            HLimmin = 0;
            HLimmax = 84.3;
            SLimmin = 0;
            SLimmax = 127.9;
            VLimmin = 141;
            VLimmax = 255;
        }
        else if ((count_images == 3) || (count_images > 4 && count_images <= 6))
        {
            HLimmin = 0;
            HLimmax = 51.3;
            SLimmin = 0;
            SLimmax = 74;
            VLimmin = 187;
            VLimmax = 255;
        }
        else if (count_images == 7)
        {
            HLimmin = 0;
            HLimmax = 42.2;
            SLimmin = 0;
            SLimmax = 74;
            VLimmin = 178.4;
            VLimmax = 229.8;
        }
        else if (count_images == 8)
        {
            HLimmin = 0;
            HLimmax = 61.1;
            SLimmin = 0;
            SLimmax = 149.7;
            VLimmin = 184.5;
            VLimmax = 255;
        }
        else if (count_images == 9)
        {
            HLimmin = 0;
            HLimmax = 68.4;
            SLimmin = 0;
            SLimmax = 255;
            VLimmin = 190.6;
            VLimmax = 255;
        }
        else if (count_images >= 10)
        {
            HLimmin = 0;
            HLimmax = 68.4;
            SLimmin = 0;
            SLimmax = 255;
            VLimmin = 190.6;
            VLimmax = 229.8;
        }
        gtk_adjustment_set_value(Hmin_adj, HLimmin);
        gtk_adjustment_set_value(Smin_adj, SLimmin);
        gtk_adjustment_set_value(Vmin_adj, VLimmin);
        gtk_adjustment_set_value(Hmax_adj, HLimmax);
        gtk_adjustment_set_value(Smax_adj, SLimmax);
        gtk_adjustment_set_value(Vmax_adj, VLimmax);
        gtk_toggle_button_set_active(channelon_w, 1);
    }
}

/**
 * @brief  Function that makes the HSV channels values window hides.
 *
 * @param  the widget 
 */

void on_Fechar_HSV_clicked()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "HSV_Window"));
    gtk_widget_hide(w);
}

/**
 * @brief  Function that makes the rotation value window hides.
 *
 * @param  the widget 
 */

void on_Fechar_angle_clicked()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "rotation_Window"));
    gtk_widget_hide(w);
}

/**
 * @brief  Function that makes the binarization threshold value window hides.
 *
 * @param  the widget 
 */

void on_fechar_binarization_clicked()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "binarization_Window"));
    gtk_widget_hide(w);
}

/**
 * @brief  Function that makes the threshold value window hides.
 *
 * @param  the widget 
 */

void on_fechar_binarization1_clicked()
{
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "binarization_Window1"));
    gtk_widget_hide(w);
}

/**
 * @brief  Function that ends with the comunication and closes the GTK interface.
 *
 * @param  the widget 
 */

void Button_Sair_clicked_cb()
{
    data->status = 1;
    strcpy(data->data_filho, "quit");
    usleep(1000000);
    data->exist_ligacao = 0;
    gtk_main_quit();
}

/**
 * @brief  Function that ends with the comunication and closes the GTK interface but in other way when compared with the prevoius one.
 *
 * @param  the widget 
 */

void InterceptCTRL_C()
{
    data->status = 1;
    data->exist_ligacao = 0;
    strcpy(data->data_filho, "quit");
    g_print("Sair por CTRL-C\n");
    gtk_main_quit();
}

/**
 * @brief  Function that starts with the comunication, makes show up the other widgets that will compose the window and disable this button in the end
 *
 * @param  the widget 
 */

void on_Button_LigarServidor_clicked(GtkWidget *widget)
{
    GtkWidget *ant_img = GTK_WIDGET(gtk_builder_get_object(builderG, "Button_Anterior"));
    GtkWidget *prox_img = GTK_WIDGET(gtk_builder_get_object(builderG, "Button_Seguinte"));
    GtkWidget *sair = GTK_WIDGET(gtk_builder_get_object(builderG, "Button_Sair"));
    gtk_widget_show(ant_img);
    gtk_widget_show(prox_img);
    gtk_widget_show(sair);
    gtk_widget_set_sensitive(widget, FALSE);
    data->pedid_ligacao = 1;
    strcpy(data->data_filho, "estou a pedir uma ligacao ao servidor");
    data->status = 1;
    sleep(1);
    //printf("-Estado  no fim do lado connect_server status:%d\n", data->status);
    //printf("-Estado  no fim do lado connect_server pedido de ligacao:%d\n", data->pedid_ligacao);
    //printf("-Estado  no fim do lado connect_server existligacao:%d\n", data->exist_ligacao);
}

/**
 * @brief  Function that sends the previous image
 * 
 * @param  the widget 
 */

void on_Button_Anterior_clicked(GtkWidget *widget)
{
    GtkWidget *binarizacao = GTK_WIDGET(gtk_builder_get_object(builderG, "check_binarizacao"));
    GtkWidget *seguinte = GTK_WIDGET(gtk_builder_get_object(builderG, "Button_Seguinte"));
    GtkWidget *filtros = GTK_WIDGET(gtk_builder_get_object(builderG, "check_filtros"));
    GtkWidget *canais = GTK_WIDGET(gtk_builder_get_object(builderG, "check_canais"));
    GtkWidget *rotacao = GTK_WIDGET(gtk_builder_get_object(builderG, "check_rotacao"));
    GtkWidget *recomendados = GTK_WIDGET(gtk_builder_get_object(builderG, "check_recomendados"));
    GtkWidget *recbin = GTK_WIDGET(gtk_builder_get_object(builderG, "check_recbin"));
    GtkWidget *reccann = GTK_WIDGET(gtk_builder_get_object(builderG, "check_reccann"));
    GtkToggleButton *valrecon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recomendados"));
    GtkToggleButton *reccan_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_reccann"));
    GtkToggleButton *recbin_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recbin"));
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "messagedialog2"));
    gboolean recbinOn = gtk_toggle_button_get_active(recbin_w);
    gboolean reccanOn = gtk_toggle_button_get_active(reccan_w);
    gboolean recHSVOn = gtk_toggle_button_get_active(valrecon_w);

    if ((recbinOn == 1) || (reccanOn == 1) || (recHSVOn == 1))
    {
        gtk_widget_show(w);
    }
    else
    {
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(seguinte, FALSE);
        count_images--;
        if (count_images == 0)
        {
            count_images--;
        }
        if (count_images > 10)
        {
            count_images = 1;
        }
        if (count_images < 0)
        {
            count_images = num_images;
        }
        //printf("Numero da imagem Botao Anterior:%d\n", count_images);
        strcpy(data->data_filho, "imagem anterior");
        data->status = 1;
        gtk_widget_show(binarizacao);
        gtk_widget_show(filtros);
        gtk_widget_show(canais);
        gtk_widget_show(recomendados);
        gtk_widget_show(rotacao);
        gtk_widget_show(recbin);
        gtk_widget_show(reccann);
        sleep(2);
        gtk_widget_set_sensitive(widget, TRUE);
        gtk_widget_set_sensitive(seguinte, TRUE);

    }
    //printf("--Estado  no fim do lado callback:%d\n", data->status);
    //printf("--Estado  no fim do lado callback:%d\n", data->pedid_ligacao);
    //printf("--Estado  no fim do lado callback:%d\n", data->exist_ligacao);
}

/**
 * @brief  Function that starts with the delivering of images 
 * 
 * @param  the widget 
 */

void on_Button_Seguinte_clicked(GtkWidget *widget)
{
    GtkWidget *binarizacao = GTK_WIDGET(gtk_builder_get_object(builderG, "check_binarizacao"));
    GtkWidget *anterior = GTK_WIDGET(gtk_builder_get_object(builderG, "Button_Anterior"));
    GtkWidget *filtros = GTK_WIDGET(gtk_builder_get_object(builderG, "check_filtros"));
    GtkWidget *canais = GTK_WIDGET(gtk_builder_get_object(builderG, "check_canais"));
    GtkWidget *rotacao = GTK_WIDGET(gtk_builder_get_object(builderG, "check_rotacao"));
    GtkWidget *recomendados = GTK_WIDGET(gtk_builder_get_object(builderG, "check_recomendados"));
    GtkWidget *recbin = GTK_WIDGET(gtk_builder_get_object(builderG, "check_recbin"));
    GtkWidget *reccann = GTK_WIDGET(gtk_builder_get_object(builderG, "check_reccann"));
    GtkToggleButton *valrecon_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recomendados"));
    GtkToggleButton *reccan_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_reccann"));
    GtkToggleButton *recbin_w = (GtkToggleButton *)(gtk_builder_get_object(builderG, (const gchar *)"check_recbin"));
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builderG, "messagedialog2"));
    gboolean recbinOn = gtk_toggle_button_get_active(recbin_w);
    gboolean reccanOn = gtk_toggle_button_get_active(reccan_w);
    gboolean recHSVOn = gtk_toggle_button_get_active(valrecon_w);

    if ((recbinOn == 1) || (reccanOn == 1) || (recHSVOn == 1))
    {
        gtk_widget_show(w);
    }
    else
    {
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(anterior, FALSE);
        count_images++;
        if (count_images == 0)
        {
            count_images++;
        }
        if (count_images > 10)
        {
            count_images = 1;
        }
        if (count_images < 0)
        {
            count_images = num_images;
        }

        //printf("Numero da image Botao Seguinte:%d\n", count_images);
        strcpy(data->data_filho, "mais uma imagem");
        data->status = 1;
        gtk_widget_show(binarizacao);
        gtk_widget_show(filtros);
        gtk_widget_show(canais);
        gtk_widget_show(recomendados);
        gtk_widget_show(rotacao);
        gtk_widget_show(recbin);
        gtk_widget_show(reccann);
        sleep(2);
        gtk_widget_set_sensitive(widget, TRUE);
        gtk_widget_set_sensitive(anterior, TRUE);
    }
    //printf("--Estado  no fim do lado callback:%d\n", data->status);
    //printf("--Estado  no fim do lado callback:%d\n", data->pedid_ligacao);
    //printf("--Estado  no fim do lado callback:%d\n", data->exist_ligacao);
}

/**
 * @brief  Handler for the timeout
 *
 *   Create a draw event in a special widget as consequence of
 *   the timeout action and ensure periodic refresh of widget.
 *
 * @param  data just to be a proper handler. Not really used. But could be some handler.
 * @return boolean to re-arm the timeout
 */

gboolean pari_UpdateMyDisplay()
{
    GtkWidget *da = GTK_WIDGET(gtk_builder_get_object(builderG, "mydrawingareasingle"));
    gtk_widget_queue_draw(da);
    da = GTK_WIDGET(gtk_builder_get_object(builderG, "DrawingArea_Processed"));
    gtk_widget_queue_draw(da);
    return TRUE; //to re-arm the timeout.
}

/**
 * @brief  Handler for the timeout
 *
 *
 * @param  data just to be a proper handler. Not really used. But could be some handler.
 * @return boolean to re-arm the timeout
 */

gboolean on_mydrawingareasingle_draw()
{
    pari_PerformImageAcquisition();
    pari_RefreshDrawingArea((char *)"mydrawingareasingle", src_imageG);
    pari_ProcessUserOperations(src_imageG, dst_imageG);
    pari_RefreshDrawingArea((char *)"DrawingArea_Processed", dst_imageG);
    return TRUE;
}