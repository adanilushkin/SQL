/*
FLIGHT(flightnum, origination, destination, miles)
MANIFEST(flightnum, flightDate, passnum, seatnum) where seat num is a row number between 1 and 50, and a letter between A and F inclusive
PASS(passnum, lastName,firstName)
*/

drop table if exists manifest;
drop table if exists passenger;
drop table if exists flight;

create table flight
	(flightnum int auto_increment primary key,
	origination char(25),
	destination char(25),
	miles int);
	
create table passenger
	(passnum int auto_increment primary key,
	lastName char(10),
	firstName char(10) );
	
create table manifest
	(flightnum int,
	flightDate date,
	passnum int,
	seatnum char(5), 
	primary key(flightnum, flightDate, passnum),
	foreign key(flightnum) references flight(flightnum) ,
	foreign key(passnum) references passenger(passnum)) ;

#now put some records in
insert into flight ( origination,destination,miles) 
	values ( 'Chicago', 'Denver', 919); #1
insert into flight ( origination,destination,miles) 
	values ('Chicago', 'Laredo', 1361);  #2
insert into flight ( origination,destination,miles) 
	values ('Saint Louis', 'Chicago', 298);  #3
insert into flight (origination,destination,miles) 
	values ('Miami', 'Denver', 2060);	#4
insert into flight ( origination,destination,miles) 
	values ( 'Denver', 'Miami', 2060);		#5

insert into passenger (firstName,lastName) 
	values ( 'John','Doe');			#1
insert into passenger (firstName,lastName) 
	values ('Michonne','Grimes');		#2
insert into passenger (firstName,lastName) 
	values ( 'Mary','Brown');		#3
insert into passenger (firstName,lastName) 
	values ( 'Sophia','Peletier');	#4
insert into passenger (firstName,lastName) 
	values ( 'Dean','Winchester');	#5
insert into passenger (firstName,lastName) 
	values ( 'Daryl','Dixon');		#6
insert into passenger (firstName,lastName) 
	values ('Harold ','Finch');		#7
insert into passenger (firstName,lastName) 
	values ('Merle','Dixon');		#8
insert into passenger (firstName,lastName) 
	values ('Shane','Walsh');		#9
insert into passenger (firstName,lastName) 
	values ('John','Reese');	#10
insert into passenger (firstName, lastName) 
	values ('Andy','Sipowicz');	#11
insert into passenger (firstName, lastName) 
	values ('Lionel','Fusco');	#12

insert into manifest (flightnum,flightDate, passnum, seatnum)  
	values (1, NOW(), 1, '5A');
insert into manifest (flightnum, flightDate, passnum, seatnum)  
	values (1, NOW(), 2, '35C');
insert into manifest (flightnum, flightDate, passnum, seatnum)  
	values (1, NOW(), 5, '20B');
insert into manifest (flightnum, flightDate, passnum, seatnum)  
	values (1, NOW(), 6, '50F');	
insert into manifest (flightnum, flightDate, passnum, seatnum)  
	values (2, NOW(), 3, '22E');
insert into manifest (flightnum, flightDate, passnum, seatnum)  
	values (2, NOW(), 4, '38C');
