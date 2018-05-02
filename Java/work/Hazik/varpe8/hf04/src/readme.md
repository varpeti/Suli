# Felépítés:

- client (Client)
    - server (Server)
        - ip (InetAddress)
        - port (int)    
    - players (arraylist< String >)    
    - mode (bool: {false: lastmanstanding, true: ratatata})    
    - table1 (Table)
        - size (Size)
            - x (int)
            - y (int)    
        - pos (Pos)
            - x (int)
            - y (int)
            - status (byte {0: water, 1: enemy ship part, 2: destroyed enemy ship part, 3: own ship part, 4: own destroyed ship part} )    
    - table2 (Table)
        - size (Size)
            - x (int)
            - y (int)    
        - pos (arraylist< Pos >)
                - x (int)
                - y (int)
                - status (byte {0: water, 1: enemy ship part, 2: destroyed enemy ship part, 3: own ship part, 4: own destroyed ship part} )
- server (Server)
    - clients (arraylist<Client>)
        name (String)
        isLeader (boolean)
    - pos (arraylist< Pos >)
        - x (int)
        - y (int)
        - status (byte {0: water, 1: ship part, 2: destroyed ship part})
        - owner (String)

# Csacsogás:

    "ok <command>" leokézza hogy megérkezett a kommand
    
### Client -> Server
    
    "hellomynameis <name>" elmondja a nevét a csatlakozó játékos
    "maxplayers <number>" a leader beállítja a maximum játékos számot
    "mode <mode>" mód kiválasztása
    "start" játék indítása
    "imout" kilépés
    "chat <what>" broadcats chat
    "kill <pos>" lövés
    
    
### Server -> Client
    
    "uarethe1st" beállítja leadernek a csatlakozó játékost
    "chat <name> joined" elmondja mindenkinek a csatlakozást
    "soyoucan" átadja a kört
    "status <status>" lövés utáni pozíció státusza

# Szálak:

### Client
    Client
    Game
    GUI

### Server
    Server