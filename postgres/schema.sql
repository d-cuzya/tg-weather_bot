create table if not exists users(
    telegramid integer primary key,
    count_msg integer default 0 not null,
    max_msg integer default 50 not null
);

create table if not exists coords(
    userid integer primary key,
    latitude numeric,
    longitude numeric,
    FOREIGN KEY (userid) REFERENCES users(telegramid) on delete cascade
);
