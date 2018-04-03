###### Introduction​ ​ to​ ​ Database​ ​ Systems

# Database for a simple forum website

Project by: **Váraljai Péter**

Project Supervisor: **Gábor​ Csaba**

---

## Introduction​

I would like to create a small database to show examples of all types of entities and relationships. I will store the data of a small forum, including useres, admins, their messages, post, and comments. (ect)

## Description

- **Board:**
Figurarly this is the "main menu" every **Room** is listed under different **Board**. It can be created or modified by any **Admin** who has a right permission level.

- **Room:**
**Room**s are attached to **Board**s. Every **Room** contain different **Post** from different **User**s. It can be created by any **User**. It has creation time, and it can be locked by any **Admin**.

- **Post:**
**Post** are attached to **Room**s or **UserWall**s. Users can **Comment** any **Post**s (except if the **Room** is locked).
It has creation time, belongs to an **User**, and contains a message.

- **Comment:**
Every **User** can **Comment** their/other **User**s **Post**.
It has creation time, belongs to an **User**, and contains a message.

- **ChatRoom:**
**Chatroom**s are automaticaly created rooms where **User**s and **Admin**s can send **Message**s to each other.
Multiple **User**s can be in the same **ChatRoom**, and **User**s can be in multiple **ChatRoom**s.

- **Message:**
Every **User** can send **Message**s to other **User**s are in the same **ChatRoom**.
It has creation time, belongs to a **User**, and contains a message.

- **AbsUser:**
This is the abstract user. It stores username and hashed and encrypted password.

- **User:**
This is an ISA subclass of AbsUser. It has registration date and **UserWall**.

- **Admin:**
This is an ISA subclass of AbsUser. It has permission level, and a **Log**ger.

- **UserWall:**
This is belongs to a **User**. Other **User**s can **Post** their opinions here.

- **Log:**
This is a weak table. It is belongs to an **Admin** and cointains every modifications an **Admin** done.


## E/R Diagramm

![ER Diagramm](./ER_diagram.png "ER Diagramm")


## Relational model

`primary key(s)`

**Board**(`name`, permissionlvl, rAdmin)

**Plvl_Board**(`rBoard`,`lvl`)

**Room**(`name`, islocked, date, time, rBoard, rAdmin)

**Post**(`id`, message, date, time, rRoom, rUserWall, rAbsUser)

**Comment**(`id`, message, date, time, rPost, rAbsUser)

**ChatRoom**(`id`)

**ChatRoom_AbsUser**(`rChatRoom`,`rAbsUser`)

**Message**(`id`, message, date, time, rChatroom, rAbsUser)

**AbsUser**(`name`, pw)

**User**(`iAbsUser`, regdate, regtime)

**Admin**(`iAbsUser`, permissionlvl)

**Plvl_Admin**(`rAdmin`,`lvl`)

**UserWall**(`rUser`)

**Log**(`rAdmin`,message)

## Querries

### 1.

Melyik az a top 10 **Post** aminek a legtöbb **Comment**je van?

What are the top 10 most popular **Post**?

```sql
select *
from 
( 
    select Post.id, count(Comment2.id) as noComments
    from Post, Comment2 
    where Comment2.rPost = Post.id
    group by Post.id
    order by noComments desc
)
where rownum <=10
;
```

### 2.

Mellyek azok a **Board**ok, és ki csinálta, amiket nem 6-os vagy 4-es jogú **Admin** készített?

What are the name of the **Board**s and who are the creators, where the creator **Admin** permissionlvl isn't 6 nor 4?

```sql
select Board.name as BoardName, AbsUser.name as AdminName
from AbsUser, Board
where AbsUser.name like Board.rAdmin
    and AbsUser.name != all 
    (
        select Admin.iAbsUser
        from Admin
        where permissionlevel = any (4,6)
    )
;
```

### 3.

Mellyek azok a **Post**ok melyek alatt a 2 legfőbb Admin is **Comment**elt (mindekető)?

What are the ids of the **Post**s, where the 2 Big Bosses are **Comment**ed (both)?   

```sql
create view TheBigBosses as
    select *
    from 
    (
        select Admin.iAbsUser as username
        from Admin
        order by Admin.permissionlevel desc
    ) 
    where rownum <=2
;

create view PnC as
    select Post.id as pid, Comment2.id as cid, Comment2.rAbsUser as username
    from Post, Comment2
    where Comment2.rPost = Post.id
;

select PnC.pid
from PnC, TheBigBosses
where PnC.username = TheBigBosses.username
group by PnC.pid
having  min(PnC.username) = ( select min(TheBigBosses.username) from TheBigBosses )
    and max(PnC.username) = ( select max(TheBigBosses.username) from TheBigBosses )
;

drop view TheBigBosses;
drop view PnC;
```
