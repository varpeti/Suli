drop table AbsUser CASCADE CONSTRAINTS;
drop table Admin CASCADE CONSTRAINTS;
drop table User2 CASCADE CONSTRAINTS;
drop table UserWall CASCADE CONSTRAINTS;
drop table Board CASCADE CONSTRAINTS;
drop table Room CASCADE CONSTRAINTS;
drop table Post CASCADE CONSTRAINTS;
drop table Comment2 CASCADE CONSTRAINTS;
drop table ChatRoom CASCADE CONSTRAINTS;
drop table ChatRoom_AbsUser CASCADE CONSTRAINTS;
drop table Message CASCADE CONSTRAINTS;
drop table Log CASCADE CONSTRAINTS;

create table AbsUser (
    name varchar2(20),
    pw varchar2(99),
    primary key (name)
);

create table Admin (
    iAbsUser varchar2(20) references AbsUser(name),
    permissionlevel number,
    primary key (iAbsUser)
);

create table Log (
    rAdmin varchar(20) not null references Admin(iAbsUser) on delete cascade,
    message varchar2(255),
    primary key (rAdmin)
);

create table User2 (
    iAbsUser varchar2(20) references AbsUser(name), 
    regdate number,
    regtime number,
    primary key (iAbsUser)
);

create table UserWall (
    rUser varchar2(20) references User2(iAbsUser),
    primary key (rUser)
);

create table Board (
    name varchar2(20), 
    permissionlvl number,
    rAdmin varchar2(20),
    foreign key (rAdmin) references Admin(iAbsUser),
    primary key (name)
);

create table Room (
    name varchar2(20),
    islocked number(1),
    datetime date,
    rBoard varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rBoard) references Board(name),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (name)
);

create table Post (
    id number,
    message varchar2(255),
    datetime date,
    rRoom varchar2(20),
    rUserWall varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rRoom) references Room(name),
    foreign key (rUserWall) references UserWall(rUser),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (id)
);

create table Comment2 (
    id number,
    message varchar2(255),
    datetime date,
    rPost number,
    rAbsUser varchar2(20),
    foreign key (rPost) references Post(id),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (id)
);

create table ChatRoom (
    name varchar2(20),
    primary key (name)
);

create table ChatRoom_AbsUser(
    rChatRoom varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rChatRoom) references ChatRoom(name),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (rChatRoom,rAbsUser)
);

create table Message (
    id number,
    message varchar2(255),
    datetime date,
    rChatRoom varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rChatRoom) references ChatRoom(name),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (id)
);

alter table User2 drop (regdate, regtime);
alter table User2 add (regdatetime date default sysdate);
alter table Room modify (datetime date default sysdate);
alter table Post modify (datetime date default sysdate);
alter table Comment2 modify (datetime date default sysdate);
alter table Message modify (datetime date default sysdate);
insert into AbsUser values ('Woccvjdcv','381516116986927249');
insert into Admin values ('Woccvjdcv','6');
insert into Log values ('Woccvjdcv','Woccvjdcv created.');
insert into AbsUser values ('Zmfjm4','1337080314759695572');
insert into Admin values ('Zmfjm4','5');
insert into Log values ('Zmfjm4','Zmfjm4 created.');
insert into AbsUser values ('tlkry','985350846654597406');
insert into Admin values ('tlkry','4');
insert into Log values ('tlkry','tlkry created.');
insert into AbsUser values ('pndkujcbt','581606091234203312');
insert into Admin values ('pndkujcbt','3');
insert into Log values ('pndkujcbt','pndkujcbt created.');
insert into AbsUser values ('OjozdrUio','1343219880855447503');
insert into Admin values ('OjozdrUio','2');
insert into Log values ('OjozdrUio','OjozdrUio created.');
insert into AbsUser values ('IyMkzbqwq','76007224854398785');
insert into Admin values ('IyMkzbqwq','1');
insert into Log values ('IyMkzbqwq','IyMkzbqwq created.');
insert into AbsUser values ('praJV','1009664613864804624');
insert into Admin values ('praJV','0');
insert into Log values ('praJV','praJV created.');
insert into AbsUser values ('TgDyqrhbk','2594986441070144096');
insert into Admin values ('TgDyqrhbk','0');
insert into Log values ('TgDyqrhbk','TgDyqrhbk created.');
insert into AbsUser values ('GgnEHh','1325310988349815882');
insert into Admin values ('GgnEHh','0');
insert into Log values ('GgnEHh','GgnEHh created.');
insert into AbsUser values ('Fcrpi537','566885247751157308');
insert into Admin values ('Fcrpi537','0');
insert into Log values ('Fcrpi537','Fcrpi537 created.');
insert into AbsUser values ('Ozbd386860710','542191977876665016');
insert into User2 values ('Ozbd386860710',sysdate);
insert into UserWall values ('Ozbd386860710');
insert into AbsUser values ('ebNFpvr','1178402290455848132');
insert into User2 values ('ebNFpvr',sysdate);
insert into UserWall values ('ebNFpvr');
insert into AbsUser values ('QodiNoujf','626441534805025628');
insert into User2 values ('QodiNoujf',sysdate);
insert into UserWall values ('QodiNoujf');
insert into AbsUser values ('Dbhcfjyba','13524152841390206632');
insert into User2 values ('Dbhcfjyba',sysdate);
insert into UserWall values ('Dbhcfjyba');
insert into AbsUser values ('EeCtawql','714860191469520742');
insert into User2 values ('EeCtawql',sysdate);
insert into UserWall values ('EeCtawql');
insert into AbsUser values ('Jpsydmihm','234690222273298838');
insert into User2 values ('Jpsydmihm',sysdate);
insert into UserWall values ('Jpsydmihm');
insert into AbsUser values ('Myciaywog','981815121054796726');
insert into User2 values ('Myciaywog',sysdate);
insert into UserWall values ('Myciaywog');
insert into AbsUser values ('glov','13111287211071265983');
insert into User2 values ('glov',sysdate);
insert into UserWall values ('glov');
insert into AbsUser values ('JvtnqB83137200356','1024079507326643843');
insert into User2 values ('JvtnqB83137200356',sysdate);
insert into UserWall values ('JvtnqB83137200356');
insert into AbsUser values ('kkkcha2','1169211622368697009');
insert into User2 values ('kkkcha2',sysdate);
insert into UserWall values ('kkkcha2');
insert into AbsUser values ('PbyoxH','721055652750692511');
insert into User2 values ('PbyoxH',sysdate);
insert into UserWall values ('PbyoxH');
insert into AbsUser values ('Vjzd342','1132850030326144628');
insert into User2 values ('Vjzd342',sysdate);
insert into UserWall values ('Vjzd342');
insert into AbsUser values ('kgRlZuqt','330316419203331718');
insert into User2 values ('kgRlZuqt',sysdate);
insert into UserWall values ('kgRlZuqt');
insert into AbsUser values ('Dfvhnbcx','1135459596131362761');
insert into User2 values ('Dfvhnbcx',sysdate);
insert into UserWall values ('Dfvhnbcx');
insert into AbsUser values ('Kcaios52966','1288996423117222685');
insert into User2 values ('Kcaios52966',sysdate);
insert into UserWall values ('Kcaios52966');
insert into AbsUser values ('eKEBeg','839075894601088609');
insert into User2 values ('eKEBeg',sysdate);
insert into UserWall values ('eKEBeg');
insert into AbsUser values ('sjyikpqrW','2934298391341327964');
insert into User2 values ('sjyikpqrW',sysdate);
insert into UserWall values ('sjyikpqrW');
insert into AbsUser values ('Oadazmi23','12701367692233602');
insert into User2 values ('Oadazmi23',sysdate);
insert into UserWall values ('Oadazmi23');
insert into AbsUser values ('WxvquifkX','740151999481216753');
insert into User2 values ('WxvquifkX',sysdate);
insert into UserWall values ('WxvquifkX');
insert into AbsUser values ('Swyzv6','123194726262832138');
insert into User2 values ('Swyzv6',sysdate);
insert into UserWall values ('Swyzv6');
insert into AbsUser values ('dQuQeAXPg','655002815292828895');
insert into User2 values ('dQuQeAXPg',sysdate);
insert into UserWall values ('dQuQeAXPg');
insert into AbsUser values ('uhbrmiNlc','1036806502833306691');
insert into User2 values ('uhbrmiNlc',sysdate);
insert into UserWall values ('uhbrmiNlc');
insert into AbsUser values ('Vuiact','622298096300324825');
insert into User2 values ('Vuiact',sysdate);
insert into UserWall values ('Vuiact');
insert into AbsUser values ('hurkzvfgi','1002066780522182570');
insert into User2 values ('hurkzvfgi',sysdate);
insert into UserWall values ('hurkzvfgi');
insert into AbsUser values ('tfps43171','914623983493567456');
insert into User2 values ('tfps43171',sysdate);
insert into UserWall values ('tfps43171');
insert into AbsUser values ('Pjxaoeolp','28221881922512402');
insert into User2 values ('Pjxaoeolp',sysdate);
insert into UserWall values ('Pjxaoeolp');
insert into AbsUser values ('mrDf127293','693656979675010007');
insert into User2 values ('mrDf127293',sysdate);
insert into UserWall values ('mrDf127293');
insert into AbsUser values ('upeh','410463134761163429');
insert into User2 values ('upeh',sysdate);
insert into UserWall values ('upeh');
insert into AbsUser values ('Aqkzranh','44975096799899535');
insert into User2 values ('Aqkzranh',sysdate);
insert into UserWall values ('Aqkzranh');
insert into AbsUser values ('ivkd72','945557464611624497');
insert into User2 values ('ivkd72',sysdate);
insert into UserWall values ('ivkd72');
insert into AbsUser values ('qjpb3','3117717711153088286');
insert into User2 values ('qjpb3',sysdate);
insert into UserWall values ('qjpb3');
insert into AbsUser values ('RfLn2','9220479931249750397');
insert into User2 values ('RfLn2',sysdate);
insert into UserWall values ('RfLn2');
insert into AbsUser values ('fjxlp88','1190440421750537177');
insert into User2 values ('fjxlp88',sysdate);
insert into UserWall values ('fjxlp88');
insert into AbsUser values ('Zlbtrfdd','503505783655975958');
insert into User2 values ('Zlbtrfdd',sysdate);
insert into UserWall values ('Zlbtrfdd');
insert into AbsUser values ('qotkVnb','1148909794787472734');
insert into User2 values ('qotkVnb',sysdate);
insert into UserWall values ('qotkVnb');
insert into AbsUser values ('rXmhxjUq','340237038184886577');
insert into User2 values ('rXmhxjUq',sysdate);
insert into UserWall values ('rXmhxjUq');
insert into AbsUser values ('esBdbIttv','1269286990469939594');
insert into User2 values ('esBdbIttv',sysdate);
insert into UserWall values ('esBdbIttv');
insert into AbsUser values ('VrhmohWsl','603925111261867856');
insert into User2 values ('VrhmohWsl',sysdate);
insert into UserWall values ('VrhmohWsl');
insert into AbsUser values ('Tezyf','320227963454879726');
insert into User2 values ('Tezyf',sysdate);
insert into UserWall values ('Tezyf');
insert into AbsUser values ('IxdTw70','411169635295787453');
insert into User2 values ('IxdTw70',sysdate);
insert into UserWall values ('IxdTw70');
insert into AbsUser values ('fxkqp8348','7868297180955992');
insert into User2 values ('fxkqp8348',sysdate);
insert into UserWall values ('fxkqp8348');
insert into AbsUser values ('Yhznl86','811167638136703020');
insert into User2 values ('Yhznl86',sysdate);
insert into UserWall values ('Yhznl86');
insert into AbsUser values ('kmcjdxwb','918715100600409630');
insert into User2 values ('kmcjdxwb',sysdate);
insert into UserWall values ('kmcjdxwb');
insert into AbsUser values ('kbhlxgsev','1136017996864291721');
insert into User2 values ('kbhlxgsev',sysdate);
insert into UserWall values ('kbhlxgsev');
insert into AbsUser values ('AheszrFcD','1054344217234954814');
insert into User2 values ('AheszrFcD',sysdate);
insert into UserWall values ('AheszrFcD');
insert into AbsUser values ('AgTtye','89548824727101174');
insert into User2 values ('AgTtye',sysdate);
insert into UserWall values ('AgTtye');
insert into AbsUser values ('Numvzzb7509','7187152741385902757');
insert into User2 values ('Numvzzb7509',sysdate);
insert into UserWall values ('Numvzzb7509');
insert into AbsUser values ('OaidSykdr','10409459201265455351');
insert into User2 values ('OaidSykdr',sysdate);
insert into UserWall values ('OaidSykdr');
insert into AbsUser values ('Jqxve','448584042712127217');
insert into User2 values ('Jqxve',sysdate);
insert into UserWall values ('Jqxve');
insert into AbsUser values ('gqscyv1','1202966408735347955');
insert into User2 values ('gqscyv1',sysdate);
insert into UserWall values ('gqscyv1');
insert into AbsUser values ('josvh961','78456359990637837');
insert into User2 values ('josvh961',sysdate);
insert into UserWall values ('josvh961');
insert into AbsUser values ('xisqz49','465044199830749039');
insert into User2 values ('xisqz49',sysdate);
insert into UserWall values ('xisqz49');
insert into AbsUser values ('MvHnNt4','923132469766260272');
insert into User2 values ('MvHnNt4',sysdate);
insert into UserWall values ('MvHnNt4');
insert into AbsUser values ('YdLkfazay','556373752140744919');
insert into User2 values ('YdLkfazay',sysdate);
insert into UserWall values ('YdLkfazay');
insert into AbsUser values ('Ojgs','2523910991205766550');
insert into User2 values ('Ojgs',sysdate);
insert into UserWall values ('Ojgs');
insert into AbsUser values ('ztzqlgjy','1159150193269803819');
insert into User2 values ('ztzqlgjy',sysdate);
insert into UserWall values ('ztzqlgjy');
insert into AbsUser values ('xnZiblafu','38290939042395072');
insert into User2 values ('xnZiblafu',sysdate);
insert into UserWall values ('xnZiblafu');
insert into AbsUser values ('nKfjih8','35880108381111231');
insert into User2 values ('nKfjih8',sysdate);
insert into UserWall values ('nKfjih8');
insert into AbsUser values ('sLgx','1363482771121885834');
insert into User2 values ('sLgx',sysdate);
insert into UserWall values ('sLgx');
insert into AbsUser values ('buntawy6','965368430387654508');
insert into User2 values ('buntawy6',sysdate);
insert into UserWall values ('buntawy6');
insert into AbsUser values ('EluTotrkj','1166288317958191065');
insert into User2 values ('EluTotrkj',sysdate);
insert into UserWall values ('EluTotrkj');
insert into AbsUser values ('dtfupk','8803931641167426862');
insert into User2 values ('dtfupk',sysdate);
insert into UserWall values ('dtfupk');
insert into AbsUser values ('Tpixo6','773990538734398430');
insert into User2 values ('Tpixo6',sysdate);
insert into UserWall values ('Tpixo6');
insert into AbsUser values ('irdhx','737967461307720168');
insert into User2 values ('irdhx',sysdate);
insert into UserWall values ('irdhx');
insert into AbsUser values ('upigylu','962062676797381363');
insert into User2 values ('upigylu',sysdate);
insert into UserWall values ('upigylu');
insert into AbsUser values ('Fxmxr30','5013307641163425706');
insert into User2 values ('Fxmxr30',sysdate);
insert into UserWall values ('Fxmxr30');
insert into AbsUser values ('Cmug','386701974611276620');
insert into User2 values ('Cmug',sysdate);
insert into UserWall values ('Cmug');
insert into AbsUser values ('ixhim52','6442393571038226940');
insert into User2 values ('ixhim52',sysdate);
insert into UserWall values ('ixhim52');
insert into AbsUser values ('ffpog','861004411252126037');
insert into User2 values ('ffpog',sysdate);
insert into UserWall values ('ffpog');
insert into AbsUser values ('WvavAu9246','13908671181303157976');
insert into User2 values ('WvavAu9246',sysdate);
insert into UserWall values ('WvavAu9246');
insert into AbsUser values ('nqrgl5','102125084076870681');
insert into User2 values ('nqrgl5',sysdate);
insert into UserWall values ('nqrgl5');
insert into AbsUser values ('bbjddoeIm','872318184183809579');
insert into User2 values ('bbjddoeIm',sysdate);
insert into UserWall values ('bbjddoeIm');
insert into AbsUser values ('qeefpqqd','673245369122740241');
insert into User2 values ('qeefpqqd',sysdate);
insert into UserWall values ('qeefpqqd');
insert into AbsUser values ('Hhhaflyo','388139806415259775');
insert into User2 values ('Hhhaflyo',sysdate);
insert into UserWall values ('Hhhaflyo');
insert into AbsUser values ('pYEw','242441976509083651');
insert into User2 values ('pYEw',sysdate);
insert into UserWall values ('pYEw');
insert into AbsUser values ('Kdqbz5','7362184961157687437');
insert into User2 values ('Kdqbz5',sysdate);
insert into UserWall values ('Kdqbz5');
insert into AbsUser values ('Kxwj570','501733709966512148');
insert into User2 values ('Kxwj570',sysdate);
insert into UserWall values ('Kxwj570');
insert into AbsUser values ('ttfgb','659840651190959924');
insert into User2 values ('ttfgb',sysdate);
insert into UserWall values ('ttfgb');
insert into AbsUser values ('Ahoa139','7379347231179059566');
insert into User2 values ('Ahoa139',sysdate);
insert into UserWall values ('Ahoa139');
insert into AbsUser values ('amtimm80195922','1221715198740907897');
insert into User2 values ('amtimm80195922',sysdate);
insert into UserWall values ('amtimm80195922');
insert into AbsUser values ('Hbmc3','1140223293325535047');
insert into User2 values ('Hbmc3',sysdate);
insert into UserWall values ('Hbmc3');
insert into AbsUser values ('Koik','341863561887154709');
insert into User2 values ('Koik',sysdate);
insert into UserWall values ('Koik');
insert into AbsUser values ('ewkyb','6136237141316448947');
insert into User2 values ('ewkyb',sysdate);
insert into UserWall values ('ewkyb');
insert into AbsUser values ('Qbmud7223','31297507455176866');
insert into User2 values ('Qbmud7223',sysdate);
insert into UserWall values ('Qbmud7223');
insert into AbsUser values ('jztm566','12655318611157375974');
insert into User2 values ('jztm566',sysdate);
insert into UserWall values ('jztm566');
insert into AbsUser values ('pGgxg68','1345655465147817538');
insert into User2 values ('pGgxg68',sysdate);
insert into UserWall values ('pGgxg68');
insert into AbsUser values ('hfmk1','424645622221421607');
insert into User2 values ('hfmk1',sysdate);
insert into UserWall values ('hfmk1');
insert into AbsUser values ('KtirxWf','579121121574825539');
insert into User2 values ('KtirxWf',sysdate);
insert into UserWall values ('KtirxWf');
insert into AbsUser values ('vzpdnumkg','1288962861634472599');
insert into User2 values ('vzpdnumkg',sysdate);
insert into UserWall values ('vzpdnumkg');
insert into AbsUser values ('vtdxm','1006114533776960441');
insert into User2 values ('vtdxm',sysdate);
insert into UserWall values ('vtdxm');
insert into AbsUser values ('Llmuhtp2','808778990232075548');
insert into User2 values ('Llmuhtp2',sysdate);
insert into UserWall values ('Llmuhtp2');
insert into AbsUser values ('qusht','1324964009326757394');
insert into User2 values ('qusht',sysdate);
insert into UserWall values ('qusht');
insert into AbsUser values ('NuzX16795','801871523653953041');
insert into User2 values ('NuzX16795',sysdate);
insert into UserWall values ('NuzX16795');
insert into AbsUser values ('KdhdooZzs','593040730758003553');
insert into User2 values ('KdhdooZzs',sysdate);
insert into UserWall values ('KdhdooZzs');
insert into AbsUser values ('Wkwwd33','6638511991225362616');
insert into User2 values ('Wkwwd33',sysdate);
insert into UserWall values ('Wkwwd33');
insert into AbsUser values ('Vufodhee','362328061733306299');
insert into User2 values ('Vufodhee',sysdate);
insert into UserWall values ('Vufodhee');
insert into AbsUser values ('Uzivqzxry','2117793781312872977');
insert into User2 values ('Uzivqzxry',sysdate);
insert into UserWall values ('Uzivqzxry');
insert into AbsUser values ('hvxxf33','399965356420188945');
insert into User2 values ('hvxxf33',sysdate);
insert into UserWall values ('hvxxf33');
insert into AbsUser values ('ehpuvdb9','323924191320378257');
insert into User2 values ('ehpuvdb9',sysdate);
insert into UserWall values ('ehpuvdb9');
insert into AbsUser values ('Kzrszlw5','1125207557973749678');
insert into User2 values ('Kzrszlw5',sysdate);
insert into UserWall values ('Kzrszlw5');