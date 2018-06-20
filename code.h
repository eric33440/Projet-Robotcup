#ifndef FP6_H_
#define FP6_H_
#define kicker_adc 0x02
#define ball_adc 0x03
#define	cmd_motor	PTAD_PTAD7
#define  cmd_solenoide	PTAD_PTAD6
#define  controleur_mode	PTAD_PTAD1
#define	chargePin	PTAD_PTAD0
void detection_balle(void);
void delay_10us(unsigned char time);
void kicker(void);
unsigned char get_adc (unsigned char channel);
void adc_init(void);
void capture_balle(void);
#endif /* FP6_H_ */
