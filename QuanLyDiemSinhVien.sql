create database QLDSV --quan ly diem sinh vien
use QLDSV
create table khoa (
	makhoa nvarchar(10) primary key,
	tenkhoa nvarchar(30) not null
)

create table monhoc (
	mamh nvarchar(10) primary key,
	tenmh nvarchar(50) not null,
	makhoa nvarchar(10),
	foreign key(makhoa) references khoa (makhoa)
)

create table sinhvien(
	mssv nvarchar(10) primary key,
	hoten nvarchar(30) not null,
	ngaysinh nvarchar(10) not null,
	noisinh nvarchar(50),
	makhoa nvarchar(10),
	email nvarchar(50),
	sdt nvarchar(10)
	foreign key(makhoa) references khoa(makhoa)
)

create table lop (
	malop nvarchar(10) primary key,
	tenlop nvarchar(50) not null,
	mamh nvarchar(10),
	soluong int,
	ngaybatdau nvarchar(10),
	ngayketthuc nvarchar(10),
	ghichu nvarchar(50),
	foreign key (mamh) references monhoc(mamh)
)
create table ketqua(
	massv nvarchar(10),
	malop nvarchar(10),
	diem float,
	primary key (massv, malop),
	foreign key (massv) references sinhvien(mssv),
	foreign key (malop) references lop(malop)

)

create table roleuser(
	ID int identity (1,1) primary key,
	rolename nvarchar(20)
)
create table nguoidung(
	ID int identity(1,1) primary key,
	username nvarchar(50),
	pwd nvarchar(50),
	roleID int,
	foreign key (roleID) references roleuser(ID)
)

