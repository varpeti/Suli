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