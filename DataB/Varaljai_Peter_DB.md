###### Introduction​ ​ to​ ​ Database​ ​ Systems

# Database for a simple forum website

Project by: **Váraljai Péter**

Project Supervisor: **Gábor​ Csaba**

---

## Introduction​

I would like to create a small database to show examples of all types of entities and relationships. I will store the data of a small forum, including useres, admins, their messages, post, and comments. (ect)

## Description

- **Board:**
Figurarly this is the "main menu" every Room is listed under different board. It can be created or modified by any admin who has a right permission level.

- **Room:**
Rooms are attached to boards. Every room contain different post from different useres. It can be created by any user. It has creation time, and it can be locked by any admin.

- **Post:**
Post are attached to rooms or user walls. Users can comment any posts (except if the room is locked).
It has creation time, belongs to an user, and contains a message.

- **Comment:**
Every user can comment their/other users post.
It has creation time, belongs to an user, and contains a message.

- **ChatRoom:**
Chatrooms are automaticaly created rooms where users and admins can send messages to each other.
Multiple users can be in the same chat room, and users can be in multiple rooms.

- **Message:**
Every user can send messages to other users are in the same room.
It has creation time, belongs to a user, and contains a message.

- **AbsUser:**
This is the abstract user. It stores username and hashed and encrypted password.

- **User:**
This is an ISA subclass of AbsUser. It has registration date.

- **Admin:**
This is an ISA subclass of AbsUser. It has permission level.

- **UserWall:**
This is a weak entity, it belongs to a user.


## E/R Diagramm

```
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

```
