board (entity)
    name (string)
    id (string){pk}

thread (entity)
    id (integer){pk}

post (entity)
    id (integer){pk}
    message (string)

postInfo (entity)
    id (integer){pk}
    user (string)
    date (date)
    time (time)
    picture (boolean)
        
replies (ISA|post)
    backlink (integer)

board_thread (relation|o2m)

thread_post (relation|o2o)

post_postInfo (relation|o2o)

thread_replies (relation|o2m)
