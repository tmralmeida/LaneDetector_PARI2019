/*File generated automatically in samsung29 by tiago on qui jan 31 11:39:55 WET 2019*/
#ifdef __cplusplus
extern "C" {
#endif
/* callbacks.c */
void Button_Sair_clicked_cb ();
void InterceptCTRL_C ();
void on_Button_Ajuda_clicked ();
void on_Button_Anterior_clicked (GtkWidget * widget);
void on_Button_LigarServidor_clicked (GtkWidget * widget);
void on_Button_Seguinte_clicked (GtkWidget * widget);
void on_Fechar_HSV_clicked ();
void on_Fechar_angle_clicked ();
void on_check_binarizacao_toggled ();
void on_check_canais_toggled ();
void on_check_filtros_toggled ();
void on_check_recbin_toggled ();
void on_check_reccann_toggled ();
void on_check_recomendados_toggled ();
void on_check_rotacao_toggled ();
void on_fechar_binarization1_clicked ();
void on_fechar_binarization_clicked ();
gboolean on_mydrawingareasingle_draw ();
gboolean pari_UpdateMyDisplay ();
#ifdef __cplusplus
}
#endif
/* myf.cpp */
int ChildMain3 (int argc, char *argv[]);
int GetSharedMem ();
void MessageFromChild (char *str);
void MessageFromParent (char *str);
int ParentMain3 (int argc, char *argv[]);
void UserOperationBinarization (IplImage * src, IplImage * dst, GtkBuilder * gb, gpointer check_binarizacao, gpointer adjustment_binarizacao);
void UserOperationCanny (IplImage * src, IplImage * dst, GtkBuilder * gb, gpointer check_filtros, gpointer adjustment_canny);
void UserOperationHSV (IplImage * src, IplImage * dst, GtkBuilder * gb, gpointer check_canais, gpointer adjustment_Hmin, gpointer adjustment_Hmax, gpointer adjustment_Smin, gpointer adjustment_Smax, gpointer adjustment_Vmin, gpointer adjustment_Vmax);
void UserOperationRotation (IplImage * src, IplImage * dst, GtkBuilder * gb, gpointer check_rotacao, gpointer adjustment_angle);
GdkPixbuf *pari_ConvertOpenCv2Gtk (IplImage * image, int dst_w, int dst_h);
void pari_PerformImageAcquisition ();
void pari_ProcessUserOperations (IplImage * src, IplImage * dst);
void pari_RefreshDrawingArea (char *widgetName, IplImage * img);
/* client.cpp */
int main (int argc, char *argv[]);
