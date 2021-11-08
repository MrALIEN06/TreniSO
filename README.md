# TreniSO

## Modalità

### ETCS1
In questa modalità come prima cosa vengano generati tutti gli elementi necessari al funzionamento, la struttura della ferrovia costituita da binari secondo le specifiche del progetto, per ogni binario viene creato un file a lui assegnato per contenere il proprio stato (0=vuoto, 1=pieno), successivamente alla ferrovia vengano generati i cinque treni con i loro file di log.
Una volta che è stata generata tutta la struttura il processo terminale avvia un processo figlio per ogni treno, dopo l'avvio dei singoli processi invia un segnale a quest'ultimi per avviarli, in questa maniera ci si assicura che i processi figli si avviino il più possibile all'unisono.
Come ultima cosa il processo padre rimane in attesa del termine dei processi figli, se qualora uno o più di questi processi terminasse generando un'eccezione il padre terminerebbe anche gli altri processi figli.

Il singolo processo figlio, invece, prende in carica un differente treno e ne gestisce il movimento, secondo le specifiche assegnate.
Partendo sempre da una stazione il primo inserimento è avviene in automatico, i successivi invece dipenderanno dal contenuto del file relativo al binario successivo, se questo binario è vuoto (il file contiene 0) il treno si sposta su tale binario, altrimenti rimane fermo sul binario attuale.
Una volta raggiunta la stazione di arrivo il treno ci si posiziona e concluderà il proprio processo.


### ETCS2
In tale modalità si avvieranno due processi (su due shell distinte), ed entrambi generano una loro struttura, nel caso del client il processo è identico alla modalità ETCS1, mentre nel caso del server vengano generati le solite strutture ma in maniera virtuale, cioè ogni riferimento ai file viene omesso.
Dopo la creazione delle strutture il client trasmette gli itinerari dei propri treni, che vengano ricevuti dal server RBC che li memorizza in treni virtuali.
Una volta concluso l'invio degli itinerari il processo client genera un processo figlio per ogni treno e rimane in attese che tali processi terminino, se qualora uno o più di questi processi terminasse generando un'eccezione il padre terminerebbe anche gli altri processi figli.

Ogni singolo processo figlio del client prende in carica un differente treno, e ne gestisce le richieste al server RBC.
Ad ogni movimento il processo invierà una richiesta al server RBC per sapere se può o meno accedere al segmento successivo, se la richiesta viene accettata notifica al server quando lo spostamento viene terminato, altrimenti rimane fermo sul binario attuale.
Una volta richiesto il permesso di entrare nella stazione di arrivo ed effettuato il movimento il processo termina.

Nel mentre dal lato server, dopo che la ricezione degli itinerari è conclusa, esso entra in un loop in cui rimane in ascolto per eventuali richieste da parte dei processi treni.
Dopo aver ricevuto una richiesta, da parte di un treno, il server RBC controlla che il binario richiesto sia libero controllando nella propria struttura virtuale, e notifica al processo richiedente la sua decisione.
Se l'autorizzazione è negata conclude la connessione e ritorna in ascolto, pronto a servire una nuova richiesta.
Mentre se l'autorizzazione è concessa aspetta che il processo treno gli notifichi l'effettiva esecuzione del movimento, alla ricezione di quest'ultima anch'esso muove il treno virtuale corrispondente e poi ritorna in ascolto.
Una volta che tutti i treni hanno concluso il proprio percorso terminal il proprio processo.


## Compilazione

### Make

#### `make setup`
Genera le cartelle `./file/binari/`, `./file/itinerari/` e `./file/log/` necessarie all'esecuzione del progetto, ed infine decomprime l'archivio zip contenente gli itinerari nella cartella corrispondente.


#### `make all`
Compila i file necessari secondo un ordine prestabilito relativo alle dipendenze fra i vari componenti del progetto, in caso di modifiche ricompila i soli file dipendente dalla modifica effettuata.

Decommentando nel `makefile` la riga `#DEBUG =-DDEBUG -g` è possibile attivare tutte le funzioni di debug del progetto, senza andarle ad attivarle sui singoli file.
Ovviamente tale modifica richiede l'esecuzione del comando `make clean` e la ricompilazione totale del progetto.


#### `make clean`
Elimina i file binari non necessari, costringendo, se necessario, ad un eventuale totale ricompilazione del codice.


### Struttura
I file necessari alla compilazione sono mantenuti nella cartella principale, mentre i file necessari all'esecuzione hanno cartelle specifiche all'interno di un percorso prestabilito:
- `./file/binari/` -> contiene i file che memorizzano lo stato dei binari;
- `./file/itinerari/` -> contiene gli itinerari dei treni, decompressi dal file .zip;
- `./file/log/` -> contiene i log dei treni e del server RBC;


## Esecuzione
Il progetto è eseguibile in due modalità ETCS1 e ETCS2.

### Modalità ETCS1
In tale modalità è necessaria una sola shell e avviare il comando `./Treni ETCS1` saranno i processi dei singoli treni ad autogestire gli accessi ai segmenti di binario successivi.

### Modalità ETCS2
In questa Modalità sono, invece, necessarie due shell, la prima su cui si avvia il processo server con il comando `./Treni ETCS2 RBC` che si occupa di gestire le richieste ricevute da parte del processo avviato sulla seconda shell con il comando `./Treni ETCS2`.
