select *
from 
( 
    select Post.id, count(Comment2.id) as Comments
    from Post, Comment2 
    where Comment2.rPost = Post.id
    group by Post.id
    order by Comments desc
)
where rownum <=10
;



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



select count(*) as num_of_R_P_C
from Comment2, Admin
where Comment2.rAbsUser = Admin.iAbsUser
union
select count(*)
from Post, Admin
where Post.rAbsUser = Admin.iAbsUser
union
select count(*)
from Room, Admin
where Room.rAbsUser = Admin.iAbsUser
;



select Comment2.rAbsUser as Wall_Of_Shame
from Comment2 
where Comment2.message like '%yyg%'
union
select Post.rAbsUser
from Post
where Post.message like '%yyg%'
union
select Message.rAbsUser
from Message
where Message.message like '%yyg%'
minus
select Admin.iAbsUser 
from Admin
;


select UserName, count(Post.id) as Wall_Posts, (cast(days/365 as int)) as Age
from Post, UserWall,
(
    select *
    from
    (
        select User2.iAbsUser as UserName, (sysdate - User2.regdatetime) as days
        from User2
        order by days desc
    )
    where rownum <= 5
)
where Post.rUserWall = UserWall.rUser
    and  UserWall.rUser = UserName
group by UserName, days
order by days desc 
;