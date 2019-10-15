#include"laberinto.h"
#include<stdbool.h>
#include"copa.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

/*
 *PRE: Recibe la estructura jugador y el laberinto que se visualiza.
 *POS: Elimina la anterior posicion del jugador del laberinto.
 */
void limpiar_jugador(jugador_t* jugador, char laberinto[TAMANIO][TAMANIO]){
	laberinto[jugador->posicion.fil][jugador->posicion.col]=VACIO;
}

/*
 *PRE: Recibe la estructura rival y el laberinto que se visualiza.
 *POS: Elimina la anterior posicion del rival del laberinto.
 */
void limpiar_rival(rival_t* rival, char laberinto[TAMANIO][TAMANIO]){
	laberinto[rival->posicion.fil][rival->posicion.col]=VACIO;
}

/*
 *PRE: Recibe una tecla, la estructura del juego y el turno.
 *POS: Solicita al usuario que ingrese una tecla en base a la que se realizara un movimiento dentro del laberinto. Ademas muetra el turno en el que se encuentra el jugador.
 */
void solicitar_movimiento(char* tecla, juego_t juego, int turno){
	do{
		printf("\nEs su turno (%i).\nPresione:\n-'a' para desplazarse hacia la IZQUIERDA.\n-'d' para desplazarse hacia la DERECHA.\n-'w' para desplazarse hacia ARRIBA.\n-'s' para desplazarse hacia ABAJO.\n", turno);
		scanf(" %c", tecla);
	}while(!es_movimiento_valido(&juego,*tecla));
}

/*
 *PRE: Recibe la estructura juego.
 *POS: Muestra la vida actual y los objetos que se encuentran en el vector de ayudas del jugador.
 */
void mostrar_vida_y_mochila(juego_t juego) {
    printf("Vida actual: %i, ", juego.jugador.vida);
    printf("Mochila: ["  );
    for (int i=0; i<juego.jugador.tope_ayudas; i++){
       printf(" %c ", juego.jugador.ayudas[i].codigo);
    }
    printf("]\n");
}


int main(){
	juego_t juego;
	char laberinto[TAMANIO][TAMANIO];
	char tecla;
	int turno=1;

	inicializar_laberinto(&juego);
	actualizar_laberinto(juego, laberinto);
	mostrar_laberinto(laberinto);
	
	do {
		solicitar_movimiento(&tecla,juego,turno);
		limpiar_jugador(&juego.jugador, laberinto);
		mover_jugador((&juego.jugador),tecla);
		limpiar_rival(&juego.rival,laberinto); 
		mover_rival(&juego);
		actualizar_juego(&juego);
		actualizar_laberinto(juego, laberinto);
		mostrar_laberinto(laberinto);
		mostrar_vida_y_mochila(juego);
		turno++;
	} while (estado_juego(juego)==0);

	if (estado_juego(juego)==1){
		printf("GANASTE! :)\n");
	}
	else {
		printf("PERDISTE. Mejor suerte la proxima :(.\n");
	}
	return 0;
}