#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>


	mpz_t  	  alice_x;
	mpz_t  	  alice_y;
	mpz_t  		field;
	GtkWidget				       *janela, 
	   	 							*botao, 
	   	 							*entry,
	   	 							  *bar, 
	   	 							*table,
	   	 						   *dialog, 
	   	 							*label;
	GtkAdjustment                     *adj;

/* FUNCTION DECLARATION*/
void DOUBLE( mpz_t 			 P_x,
			 mpz_t  		 P_y,
			 mpz_t 			fiel,
			 mpz_t    		   a,
			 mpz_t    		   b,
			 mpz_t    	result_x,
			 mpz_t     result_y);


/* FUNCTION DECLARATION*/

void cliquecrypto();


void cliquedescrypto();



void ADD(mpz_t  		P_x,
		 mpz_t  		P_y,
		 mpz_t  		Q_x,
		 mpz_t  		Q_y,
		 mpz_t 		   fiel,
		 mpz_t    		  a,
		 mpz_t    		  b,
		 mpz_t 	   result_x,
		 mpz_t 	  result_y);


void criptografando();


void descriptografando();

void lendo_descrypto();

void sair();

void callPOP(char step[100]);

int main (int argc, char **argv){

/* DECLARAÇÃO DE VARIAVEIS*/
	mpz_t  		  P_x;
	mpz_t  		  P_y;
	mpz_t  		bob_x;
	mpz_t  		bob_y;
	mpz_t  	      Q_x;
	mpz_t  		  Q_y;
	mpz_t 	 		a;
	mpz_t    		b;
	mpz_t    result_x;
	mpz_t    result_y;
	int 	 		i;
	int 	   scalar;
	
	
	/*Inicialização da biblioteca principaç*/
	 gtk_init(&argc, &argv);

	/* INICIALIZAÇÃO VARIAVES*/
	mpz_init_set_ui(P_x, 551);
	mpz_init_set_ui(P_y, 1946);
	mpz_init_set_ui(Q_x, 0);
	mpz_init_set_ui(Q_y, 0);
	mpz_init_set_ui(field, 3697);
	mpz_init_set_ui(a, 373);
	mpz_init_set_ui(b, 402);
	mpz_init_set_ui(result_x, 0);
	mpz_init_set_ui(result_y, 0);
	mpz_init_set_ui(bob_x, 0);
	mpz_init_set_ui(bob_y, 0);
	mpz_init_set_ui(alice_x, 0);
	mpz_init_set_ui(alice_y, 0);
	
	/* CALCULANDO BP (BOB POINT) (KP=P+P+P+P+P...) (BOB_KEY == 815(static))*/
	DOUBLE(P_x, P_y, field, a, b, Q_x, Q_y);
	for (i = 0; i < 813; ++i)
	{
		ADD(P_x, P_y, Q_x, Q_y, field, a, b, result_x, result_y);
		mpz_set(Q_x,result_x);
		mpz_set(Q_y,result_y);
	}
	
	mpz_set(bob_x, Q_x);
	mpz_set(bob_y, Q_y);
	
	/* LIMPANDO VARIAVEIS PARA CALCULO DE [ALICE_KEY*BOB_POINT (BP)]*/
	mpz_set_ui(Q_x, 0);
	mpz_set_ui(Q_y, 0);
	mpz_set_ui(result_x, 0);
	mpz_set_ui(result_y, 0);
	
	/* CALCULO DE [ALICE_KEY*BOB_POINT (BP)]*/
	DOUBLE(bob_x, bob_y, field, a, b, Q_x, Q_y);
	for (i = 0; i < 917; ++i)
	{
		ADD(bob_x, bob_y, Q_x, Q_y, field, a, b, result_x, result_y);
		mpz_set(Q_x,result_x);
		mpz_set(Q_y,result_y);
	}

	mpz_set(alice_x, Q_x);
	mpz_set(alice_y, Q_y);

   	

	 /*Criação da janela*/
	 janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title(GTK_WINDOW (janela), "ECC  Client. (by Jonas Forte)");
	 gtk_widget_set_usize(janela, 1000, 400);
	 gtk_signal_connect(GTK_OBJECT (janela), "destroy", GTK_SIGNAL_FUNC (sair), NULL);

	 /*criação  da tabela principal*/
     table = gtk_table_new(20, 20, TRUE);
     gtk_container_add(GTK_CONTAINER (janela), table);

	 /*Criação do botão*/
	 botao = gtk_button_new_with_label("Criptografar !");
	 gtk_signal_connect(GTK_OBJECT (botao), "clicked", GTK_SIGNAL_FUNC (cliquecrypto), NULL);
	 gtk_table_attach_defaults(GTK_TABLE (table), botao, 0, 5, 10, 20);

	 /*Criação do botão*/
	 botao = gtk_button_new_with_label("Desriptografar !");
	 gtk_signal_connect(GTK_OBJECT (botao), "clicked", GTK_SIGNAL_FUNC (cliquedescrypto), NULL);
	 gtk_table_attach_defaults(GTK_TABLE (table), botao, 0, 5, 0, 10);
	 
	 
     /*Criação do label de titulo da janelade menssagem */
     label=gtk_label_new("PARA CRIPTOGRAFAR.");
     gtk_table_attach_defaults(GTK_TABLE (table), label,6, 13, 1, 2);


	 /*Criação do label de titulo da janelade menssagem */
     label=gtk_label_new("Crie um arquivo \"msg.txt\" \ncom o texto a ser criptografado,\no arquivo deve estar na pasta do \nexecutavel. Um arquivo sera criado,\n\"cryptomsg.txt\" com o textp ja\ncriptografado.");
     gtk_table_attach_defaults(GTK_TABLE (table), label,6, 13, 2, 14);


      /*Criação do label de titulo da janelade menssagem */
     label=gtk_label_new("PARA DESCRIPTOGRAFAR.");
     gtk_table_attach_defaults(GTK_TABLE (table), label,14 , 20, 1, 2);

      /*Criação do label de titulo da janelade menssagem */
     label=gtk_label_new("Será criado um arquivo\n\"descryptomsg.txt\", com a menssagem\nja descriptografado");
     gtk_table_attach_defaults(GTK_TABLE (table), label,14, 20, 2, 14);

     gtk_widget_show_all (janela);

     gtk_main();
	return(0);
}

void callPOP(char step[100]){

	printf("STEP : %s\n",step );
	dialog = gtk_message_dialog_new(GTK_WINDOW(janela),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Mensagem descriptografada:\n %s",step);
		  gtk_window_set_title(GTK_WINDOW(dialog), "Cypher!");
		  gtk_dialog_run(GTK_DIALOG(dialog));
		  gtk_widget_destroy(dialog);



}

/* Função de ativação do botão "criptografar" */
void cliquecrypto(){

		criptografando();
		dialog = gtk_message_dialog_new(GTK_WINDOW(janela),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Mensagem criptografada");
		  gtk_window_set_title(GTK_WINDOW(dialog), "Cypher!");
		  gtk_dialog_run(GTK_DIALOG(dialog));
		  gtk_widget_destroy(dialog);
		
		  

}
void cliquedescrypto(){

		descriptografando();
		lendo_descrypto();
}

void ADD(mpz_t  	P_x,
		 mpz_t  	P_y,
		 mpz_t  	Q_x,
		 mpz_t  	Q_y,
		 mpz_t 	   fiel,
		 mpz_t    	  a,
		 mpz_t    	  b,
		 mpz_t 	   P_3x,
		 mpz_t 	  P_3y){


	mpz_t temp,slope;

	mpz_init(temp);
	mpz_init_set_ui(slope,0);

	mpz_mod(P_x,P_x,fiel);
	mpz_mod(P_y,P_y,fiel);
	mpz_mod(Q_x,Q_x,fiel);
	mpz_mod(Q_y,Q_y,fiel);
	
	if(mpz_cmp_ui(P_x,0)==0 && mpz_cmp_ui(P_y,0)==0)
	 mpz_set(P_3x,Q_x); mpz_set(P_3y,Q_y);

	if(mpz_cmp_ui(Q_x,0)==0 && mpz_cmp_ui(Q_y,0)==0)
	 mpz_set(P_3x,P_x); mpz_set(P_3y,P_y);

	if(mpz_cmp_ui(Q_y,0)!=0){
		 mpz_sub(temp,fiel,Q_y);mpz_mod(temp,temp,fiel);
	}

	else{
		mpz_set_ui(temp,0);
	}	

	if(mpz_cmp(P_y,temp)==0 && mpz_cmp(P_x,Q_x)==0){
	 mpz_set_ui(P_3x,0); mpz_set_ui(P_3y,0); 
	}
	else{
		mpz_sub(temp,P_x,Q_x);
		mpz_mod(temp,temp,fiel);
		mpz_invert(temp,temp,fiel);
		mpz_sub(slope,P_y,Q_y);
		mpz_mul(slope,slope,temp);
		mpz_mod(slope,slope,fiel);
		mpz_mul(P_3x,slope,slope);
		mpz_sub(P_3x,P_3x,P_x);
		mpz_sub(P_3x,P_3x,Q_x);
		mpz_mod(P_3x,P_3x,fiel);
		mpz_sub(temp,P_x,P_3x);
	    mpz_mul(P_3y,slope,temp);
		mpz_sub(P_3y,P_3y,P_y);
		mpz_mod(P_3y,P_3y,fiel);
	
	}

}


void DOUBLE(mpz_t  		P_x,
    		mpz_t  		P_y,
		 	mpz_t 	   fiel,
		 	mpz_t    	  a,
		 	mpz_t         b,
		 	mpz_t      P_3x,
		 	mpz_t     P_3y){

		
		mpz_t slope,temp;

		mpz_init(temp);
		mpz_init(slope);


		if(mpz_cmp_ui(P_y,0)!=0){
		
		/*calcula LAMBIDA*/
		mpz_mul_ui(temp,P_y,2);
		mpz_invert(temp,temp,fiel);
		mpz_mul(slope,P_x,P_x);
		mpz_mul_ui(slope,slope,3);
		mpz_add(slope,slope,a);
		mpz_mul(slope,slope,temp);
		mpz_mod(slope,slope,fiel);
		/*calcula X3*/
		mpz_mul(P_3x,slope,slope);
		mpz_sub(P_3x,P_3x,P_x);
		mpz_sub(P_3x,P_3x,P_x);
		mpz_mod(P_3x,P_3x,fiel);
		/*calcula Y3*/
		mpz_sub(temp,P_x,P_3x);
		mpz_mul(P_3y,slope,temp);
		mpz_sub(P_3y,P_3y,P_y);
		mpz_mod(P_3y,P_3y,fiel);


		}
		else{
			mpz_set_ui(P_3x,0);
			mpz_set_ui(P_3y,0);
		}

}



void criptografando(){


	char 				c='\0';
	int   					x1;
	int   					x2;
	int   		    controle=0;
	int   		    	   i=0;
	FILE 			*menssagem; 
	FILE 	 *crypto_menssagem;
	mpz_t 		alice_x_aux, alice_y_aux;

	mpz_init(alice_x_aux);
	mpz_init(alice_y_aux);

	


	if ((menssagem=fopen("msg.txt", "r"))==NULL)
		printf("ERRO NA ABERTURA DO ARQUIVO MSG\n");

	if ((crypto_menssagem=fopen("cryptomsg.txt", "w+"))==NULL)
		printf("ERRO NA ABERTURA DO ARQUIVO CRYPTOMSG\n");

	do{
		c=fgetc(menssagem);
		if((c!='\0')&&(c!=EOF)) 
			controle++;
	}while((c!='\0')&&(c!=EOF));

	c='\0';
	rewind(menssagem);

	for(i=0;i<controle;i++){
	
	    c=fgetc(menssagem);
	    if((c=='\0')||(c==EOF))
			break;

	    
	    x1= (int)c;	    
	    mpz_mul_ui(alice_x_aux,alice_x,x1);
		mpz_mod(alice_x_aux,alice_x_aux,field);
		
		gmp_fprintf(crypto_menssagem, "%Zd ", alice_x_aux);




	    c=fgetc(menssagem);
	    if((c=='\0')||(c==EOF))
			break;

	    x2= (int)c;
		mpz_mul_ui(alice_y_aux,alice_y,x2);
		mpz_mod(alice_y_aux,alice_y_aux,field);
		gmp_fprintf(crypto_menssagem, "%Zd ", alice_y_aux);


		mpz_set_ui(alice_x_aux,0);
		mpz_set_ui(alice_y_aux,0);
		x1=0;
		x2=0;

	}
	
	fclose(menssagem);
	fclose(crypto_menssagem);
}


void descriptografando(){

	char 				c='\0';
	char               num[10];
	int   					x1;
	int   					x2;
	int   		    controle=0;
	int   		    	   i=0;
	int 				   j=0;
	FILE  *descrypto_menssagem; 
	FILE 	 *crypto_menssagem;
	mpz_t          alice_x_aux;
	mpz_t 		   alice_y_aux;


	mpz_init(alice_x_aux);
	mpz_init(alice_y_aux);




	mpz_invert(alice_x,alice_x,field);
	mpz_invert(alice_y,alice_y,field);

	if ((crypto_menssagem=fopen("cryptomsg.txt", "r"))==NULL)
		printf("ERRO NA ABERTURA DO ARQUIVO CRYPTOMSG\n");

	if ((descrypto_menssagem=fopen("decryptmsg.txt", "w+"))==NULL)
		printf("ERRO NA ABERTURA DO ARQUIVO DESCRYPTOMSG\n");


	do{
		c=fgetc(crypto_menssagem);
		if((c!='\0')&&(c!=EOF)) 
			controle++;
	}while((c!='\0')&&(c!=EOF));


	c='\0';
	rewind(crypto_menssagem);
	c=fgetc(crypto_menssagem);

 	
 	for(i=0;i<controle;i++){
		
 		memset(num, '\0', 10);
		if ((c=='\0')||(c==EOF))
			break;

		while((c!=' ')&&(c!='\0')&&(c!=EOF))
		{
			num[j]=c;
			j++;
			c=fgetc(crypto_menssagem);
		}
	    
	    x1= atoi(num);
		mpz_mul_ui(alice_x_aux,alice_x,x1);
		mpz_mod(alice_x_aux,alice_x_aux,field);
		gmp_fprintf(descrypto_menssagem, "%Zd ", alice_x_aux);

	    if ((c=='\0')||(c==EOF))
			break;
		
	    j=0;
	    c=fgetc(crypto_menssagem);
		memset(num, '\0', 10);

	    if ((c=='\0')||(c==EOF))
			break;
		
		while((c!=' ')&&(c!='\0')&&(c!=EOF))
		{
			num[j]=c;
			j++;
			c=fgetc(crypto_menssagem);
		}
	    
	    x2= atoi(num);
		mpz_mul_ui(alice_y_aux,alice_y,x2);
		mpz_mod(alice_y_aux,alice_y_aux,field);
		gmp_fprintf(descrypto_menssagem, "%Zd ", alice_y_aux);


		j=0;

		if ((c=='\0')||(c==EOF))
			break;

		c=fgetc(crypto_menssagem);
		mpz_set_ui(alice_x_aux, 0);
		mpz_set_ui(alice_y_aux, 0);
		x2=0;
		x1=0;
	}
	fclose(crypto_menssagem);
	fclose(descrypto_menssagem);

}

void lendo_descrypto(){

	FILE *descrypto_menssagem;
	char 					c;
	char 			  num[10];
	int 	 j=0, numint, i=0;
	char 			step[100];

	if ((descrypto_menssagem=fopen("decryptmsg.txt", "r"))==NULL)
		printf("ERRO NA ABERTURA DO ARQUIVO DESCRYPTMSG\n");
	memset(step, '\0', 100);
	c=fgetc(descrypto_menssagem);
	while((c!='\0')&&(c!=EOF))
	{

		num[i]=c;
		c=fgetc(descrypto_menssagem);
		i++;

		if (c==' '){

			numint=atoi(num);
			printf("%c", numint);
			memset(num, '\0', 10);
			i=0;
			step[j]=(char)numint;
			j++;
			c=fgetc(descrypto_menssagem);

		}

	}
	callPOP(step);

}

/* Função de saida do programa*/
void sair(){

	gtk_main_quit();
}
