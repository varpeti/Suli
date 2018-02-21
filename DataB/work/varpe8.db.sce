t1 (table)

message (weak table)

MessageRoom (table)
    id (id pk)

privateMessageRoom (table)
    id (id pk)

Board (table)
    id (id pk)
    name (string)
    permissionlevel (integer)

Room (table)
    id (id pk)
    name (string)
    islocked (boolean)
    datetime (composite attribute)
        date (date)
        time (time)

Post (table)
    id (id pk)
    message (string)
    datetime (composite attribute)
        date (date)
        time (time)

Comment (table)
    id (id pk)

AbsUser (table)
    name (string id pk)
    pw (string)

User (ISP|absUser)
    registration (composite attribute)
        date (date)
        time (time)

Admin (ISP|absUser)
    permissionlevel (integer)