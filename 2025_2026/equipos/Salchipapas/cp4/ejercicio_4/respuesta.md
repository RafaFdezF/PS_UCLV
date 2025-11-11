# Ejercicio 4

Para hacer q un proceso se detenga en un intervalo de 3 segundos usaremos el sleep(3).

Lo anadiria en dentro del siguiente for en la siguiente posicion :

for(i = 0; i < nhijos; i++ ){
    ret = fork();
    if(ret > 0){           
        if(mipid != getpid()){
            while(!recibido);
        }
        kill(ret,SIGUSR1);
        waitpid(-1,NULL,0);
        sprintf(buf,"Soy el proceso %d y acabo la ejecucion\n",getpid());
        write(1,buf,strlen(buf));

        sleep(3);   // AQUI AÑADIRIA EL CODIGO PARA QUE ESPERE 3 SEGUNDOS ENTRE LA CREACION DE CADA HIJO

        exit(0);
    }
}
