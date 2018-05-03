# Protocol

## Client

- Bármilyen Stringet, address és port nélkül
    - elküldi a Servernek

## ClientEngine

- **pong**
    - semmi

- **setname**
    - beállítja a kliens nevét 
    - küld egy **hello my name is [name]**-et

## ClientGUI

## Server

- **ping**
    - válaszol egy **pong**al

- **hello my name is [name]**
    - Üdvözöl
    - Mindenkinek bejelenti hogy megérkezett [name]