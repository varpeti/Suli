--[[ 03.06
]]

AndOr
    X and true  = X
    X and false = false
    X and X     = X
    X or  true  = true
    X or  false = X
    X or  X     = X

Alapműveletek
    1 SELECT        "sigma"     -- Sor kiválasztás
    2 PROJECTION    "pi"        -- Oszlop kiválasztás
    3 Cross Product "¤"         -- Descartes szorzat, x
    4 Rename        "ro"        --
    5 Union         "U"         --
    6 Intersect     "^"         -- metszet, fordított u


--[[ 02.20 Gyak
]]

Levels of database design
    View     - external   - "user's interface"
    Logical  - conceptual - "DataB programers"
    Physical - internal   - "DataB administrators"

entity           - "is an object that represent the world's object throug it's attributes"
attributies      - "entitie's property"
relationsips     - "logical connection betwen entitie sets"
super key        - "set of attributies, uniquely identify the entity"
candidate key    - "minimal sets of attributes uniquely identify the entity"
primary key      - "chosen candidate key"

entity relationsip model
    entity set              - "single layered rectangle"
    weak entity set         - "duble layered rectangle"  --Csak a kapcsolaton keresztül van értelme
    attribute               - "single layered oval"
    derivered attribute     - "dotted line oval"         --számolt
    multi valued attribute  - "duble line oval"          --ugyan abból több
    composite attribute     - "attribute's attributes"   --több részegységből van
    primary key             - "under line"
    discriminator           - "dotted under line"
    relation                - "diamond"
        total participation - "duble line"
    weak relation           - "duble layered diamond"
    ISA                     - "triangle"                 --öröklődés


------
--gyak lapon

------

book (entity)
    title (string)
    author (string)
    book id (integer)

costumer (entity)
    name (string)
    address (string)
    idcard (integer)

costumer_book (relation|m2m)
    startdate (date)
    enddate (date)







--[[02.15 Előadás
]]
Points:
    100
        60
            30 ZH1
            30 ZH2
        20 Project
        20 SQL computer room exam


Data
Information
Metadata
Index

File managaer
Transaction managaer

DBMS = Data Base Management System

Querry, Querry language

Multi user enviroement
    Concurrent usage
    Transaction Management
    Concurrency Contrrol

Dada (base) models
    wordl ->[abstraction]-> Data model
    