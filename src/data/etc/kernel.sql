
create table kernel_extensions {
name varchar(100) primary key,
version varchar(100) not null,
installed datetime not null,
} character set utf8 collate utf8_general_ci;
