create table Board (
    name varchar2(20) primary key, 
    permissionlvl number,

    rAdmin varchar2(20),
    foreign key (rAdmin) references Admin(name)
);

create table Room (
    name varchar2(20) primary key,
    islocked number(1),
    date number,
    time number,

    rBoard varchar2(20),
    foreign key (rBoard) references Board(name)    
);

create table Post (
    id number primary key,
    message varchar2,
    date number,
    time number,

    rRoom varchar2(20),
    rUserWall varchar2(20),
    foreign key (rRoom) references Room(name),
    foreign key (rUserWall) references UserWall(name)
);

create table Comment (
    id number primary key,
    message varchar2,
    date number,
    time number,

    rPost number,
    foreign key (rPost) references Post(name)
);

create table ChatRoom (
    name varchar2(20) primary key
);

create table ChatRoom_AbsUser(
    rChatRoom varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rChatRoom) references ChatRoom(name),
    foreign key (rAbsUser) references AbsUser(name)
);

create table Message (
    id primary key,
    message varchar2,
    dattime number,

    rChatRoom varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rChatRoom) references ChatRoom(name),
    foreign key (rAbsUser) references AbsUser(name)
);

create table AbsUser (
    name varchar2(20) primary key,
    pw number encrypt
);

create table User (
    iAbsUser varchar2(20) primary key references AbsUser(name), 
    regdate number,
    regtime number
);

create table Admin (
    iAbsUser varchar2(20) primary key references AbsUser(name), 
    permissionlevel number
);

create table UserWall (
    id varchar2(20) primary key references User(name)
);

create table Log (
    id varchar(20) primary key references Admin(name) on delete cascade
);

