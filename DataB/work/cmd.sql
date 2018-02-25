create table Board (
    name varchar2(20) primary key, 
    permissionlevel number,

    rAdmin foregin key references Admin(name)
);

create table Room (
    name varchar2(20) primary key,
    islocked number(1),
    dattime number,

    rBoard foregin key references Board(name)    
);

create table Post (
    id number primary key,
    message varchar2,
    dattime number,

    rRoom foregin key references Room(name),
    rUserWall foregin key references UserWall(name)
);

create table Comment (
    id number primary key,
    message varchar2,
    dattime number,

    rPost foregin key references Post(name)
);

create table ChatRoom (
    name varchar2(20) primary key
);

create table ChatRoom_AbsUser(
    rChatRoom foregin key references ChatRoom(name),
    rAbsUser foregin key references AbsUser(name)
);

create table Message (
    id primary key,
    message varchar2,
    dattime number,

    rChatRoom foregin key references ChatRoom(name),
    rAbsUser foregin key references AbsUser(name)
);

create table AbsUser (
    name varchar2(20) primary key,
    pw number encrypt
);

create table User (
    iAbsUser varchar2(20) primary key references AbsUser(name), 
    regdate number
);

create table Admin (
    iAbsUser varchar2(20) primary key references AbsUser(name), 
    permissionlevel number
);

create table UserWall (
    id varchar2(20) primary key references User(name) on delete cascade
);

create table Log (
    id foregin key primary key references Admin(name)
);

