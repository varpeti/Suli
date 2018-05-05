# Protocol

## Client

- Bármilyen Stringet, address és port nélkül
    - elküldi a Servernek

### ClientEngine

- **pong**
    - semmi

- **setname**
    - beállítja a kliens nevét 
    - küld egy **hello my name is [name]**-et a Clientnek

- **startserver [players] [ship2] [ship3] [ship4] [ship5] [port]**
    - Elindít egy Servert a [port]-on
    - Elküldi a Clientnek a **setserver [players] [ship2] [ship3] [ship4] [ship5]** parancsot

- **startclient [address] [port]**
    - Elindít egy Clienst ami a [adress]:[port] Serverhez próbál csatlakozni.

### ClientGUI



## Server

- Bármilyen Stringet, addressel és portal
    - elküldi a address:port Clientnek

### ServerEngine

- **ping**
    - válaszol egy **pong**al

- **hello my name is [name]**
    - Mindenkinek bejelenti: **welcome [name]**

- **setserver [players] [ship2] [ship3] [ship4] [ship5]**
    - Beállítja  az értékeket
