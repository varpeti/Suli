Board (table)
    name (string pk)
    permissionlevel (integer)

Room (table)
    name (string)
    islocked (boolean)
    datetime (datetime)

Post (table)
    id (id pk)
    message (string)
    datetime (datetime)

Comment (table)
    id (id pk)
    message (string)
    datetime (datetime)

ChatRoom (table)
    name (string pk)

Message (table)
    id (id pk)
    msg (string)
    datetime (datetime)

AbsUser (table)
    name (string pk)
    pw (string)

User (ISA|absUser)
    regdate (datetime)

Admin (ISA|absUser)
    permissionlevel (integer)

Userwall (weak table)
    id (id pk)

Board_Room (relation|om)

Room_Post (relation|om)

Post_Comment (relation|om)

ChatRoom_AbsUser (relation|mm)

Board_Admin (relation|mo)

Room_AbsUser (relation|mo)

Post_AbsUser (relation|mm)

Comment_AbsUser (relation|mm)

Userwall_User (relation|oo)

Userwall_Post (relation|mm)

-----------------------------------------------------------------------------------------------------

               +------------------------------------------------------------------------------+
               |                                                                              |
               |  +-------------------------------------------------------------+             |
               |  |                                                             |             |
               |  |  +---------------------------+                              |             |
               |  |  |                           |                              v             v
[Message ]<---[AbsUser]-----+                    +---->[Room    ]---------->[Post    ]--->[Comment ]
(_id_    )    (_name_ )     |                          (_name_  )           (_id_    )    (_id_    )
(datetime)    (pw     )     |                          (datetime)           (datetime)    (datetime)
(msg     )     ^            |                          (islocked)           (message )    (message )
     ^         |            |                              ^                     ^
     |         |            |                              |                     |
     |         |            |                              |                     |
[ChatRoom]<----+          {ISA}---[Admin          ]--->[Board          ]         |
(_id_    )                  |     ((permissionlvl))    (_name_         )         |
                            |                          ((permissionlvl))         |
                            |                                                    |
                            +-----[User   ]============[:UserWall:]--------------+
                                  (regdate)            (_id_      )

