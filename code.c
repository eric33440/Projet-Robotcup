/*
 * FP6.c
 *
 *  Created on: May 30, 2018
 *      Author: Ricod
 */
#include "FP6.h"
#include "IO_Map.h"
unsigned char balle;

void detection_balle (void)
{
	unsigned char capteur;
	PTADD_PTADD7=1;
	PTADD_PTADD6=1;
	PTADD_PTADD1=1;
	PTADD_PTADD0=1;
	capteur=get_adc(ball_adc);
	if(capteur>=38)//valeur 38 est �gal approximativement � 500 mV
	{
		balle=1;
	}else 
	{
		balle= 0;
	}

}
void delay_10us(unsigned char time)//delay mesure a l'oscilloscope � 47�s suffisant car valeur comprise entre 10 ns et 10ms
{
	unsigned char i;
	for (i = 0; i <time; ++i) {

	}
}
void capture_balle(void)
{
	detection_balle();
	PTADD_PTADD7=1;//permet de mettre en sortie le port A pour pouvoir commander
	PTADD_PTADD6=1;//
	PTADD_PTADD1=1;//
	PTADD_PTADD0=1;//
	delay_10us(2);
	if (balle)
	{
		cmd_motor = 1;//comme la balle est pr�sente le moteur doit s'allumer pour capter la balle
	}else
	{
		cmd_motor = 0;//si la balle n'est pas pr�sente alors le moteur ne fera pas tourn� le rouleaux
	}
}
void kicker(void)
{
	unsigned char value_cmdr;
	detection_balle();
	PTADD_PTADD7=1;//permet de mettre en sortie le port A pour pouvoir commander
	PTADD_PTADD6=1;//
	PTADD_PTADD1=1;//
	PTADD_PTADD0=1;//
	delay_10us(2);
	value_cmdr=get_adc(kicker_adc );
	if (balle)//si la balle est vrai (ou egal � 1) alors la balle est pr�sente 
	{
		chargePin=1;//impulsion n�cessaire au controleur de charge pour s'initialiser
		delay_10us(2);//l'impulsion doit etre entre 10ns et 10ms donc comme un cycle est appromaximativement 0.24us je prend la valeur entre 10ns et 10 ms 
		chargePin=0;
		delay_10us(2);
		chargePin=1;
		if(value_cmdr<=89)//verification si le controleur est bien en charge sur le condensateur
		{
			delay_10us(4);//attente necessaire pour le controleur de charge du condensateur permettant la charge des condensateur
			cmd_solenoide=1;//ouverture du mosfet donc allumage solenoide
			delay_10us(4);//delai permettant au solenoide de recevoir toute l'energie enmagasiner par le condensateur 
			cmd_solenoide=0;	//extinction du solenoide en fermant le mosfet 
		}
	}
}
unsigned char get_adc (unsigned char channel)
{
	ADCSC1_ADCH=channel;
	while(!ADCSC1_COCO);//test si la conversion est complete
	return ADCRL;//recup�ration de la valeur convertit par le can
}
void adc_init(void){
	ADCSC2 = 0x00;//activation du can et selection de l'entr�e � selectionnn�
	ADCCFG = 0x00;
	ADCSC1_ADCO = 1;
}
