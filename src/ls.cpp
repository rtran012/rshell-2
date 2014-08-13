#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctime>
#include <iostream>
#include <string.h>

using namespace std;

void permissions( struct stat& buf ) 
{


	//Dicrectory
(buf.st_mode & S_IFREG) ? cout<< '-':
(buf.st_mode & S_IFBLK) ? cout<< 'b':
(buf.st_mode & S_IFCHR) ? cout<< 'c':
(buf.st_mode & S_IFDIR) ? cout<< 'd':
(buf.st_mode & S_IFIFO) ? cout<< 'f':
(buf.st_mode & S_IFLNK) ? cout<< 'l':
(buf.st_mode & S_IFSOCK) ? cout<<'s':
cout<<'-';

	//User
(buf.st_mode & S_IRUSR) ? cout<< 'r' : cout<<'-';
(buf.st_mode & S_IWUSR) ? cout<< 'w' : cout<<'-';
(buf.st_mode & S_IXUSR) ? cout<< 'x' : cout<<'-';

	//Group
(buf.st_mode & S_IRGRP) ? cout<< 'r' : cout<<'-';
(buf.st_mode & S_IWGRP) ? cout<< 'w' : cout<<'-';
(buf.st_mode & S_IXGRP) ? cout<< 'x' : cout<<'-';

	//All
(buf.st_mode & S_IROTH) ? cout<< 'r' << " " : cout<<'-' << " ";
(buf.st_mode & S_IWOTH) ? cout<< 'w' << " " : cout<<'-' << " ";
(buf.st_mode & S_IXOTH) ? cout<< 'x' << " " : cout<<'-' << " ";




}

void print_file( char* path, struct stat& buf ) 
{
	
	permissions(buf);
	time_t now = buf.st_mtime;
	tm * ptm = localtime(&now);
	char buffer[30];
	strftime(buffer, 30, "%b %d %H:%M:%S", ptm); 

	cout << '\t' << buf.st_nlink << '\t' 
	<< buf.st_size << '\t'
	<< buffer << '\t'
	<< path << endl; 
}

void print_directory( char* path, int width ) 
{

	unsigned char isFile = 8;
	unsigned char isDir = 4;
	DIR* dir;
	struct dirent* entry;
	
	if ( (dir = opendir (path)) != NULL) {
	
	// print all the files and directories within directory
	while ((entry = readdir (dir)) != NULL) {
	
	if( (entry -> d_name)[0] == '.') {
	continue;
}

for( int i = 0; i < width; i++ ) 
{
	cout << "\t";
}

if( entry -> d_type == isFile ) 
{
	cout << entry -> d_name << endl;	
} 
else 
{
	cout << endl;
	cout << "./" << entry -> d_name << ":" << endl;
}
if( entry -> d_type == isDir ) 
{
	strcat(path, "/");
	strcat(path, entry -> d_name);
	print_directory( path, width + 1 );
}

}

closedir (dir);

} else 
{
	//could not open directory 
	cout << "Could not open directory." << endl;
	return;
}
}


void print_default_dir( string path, int width )
{

unsigned char isDir = 0x4;
unsigned char isFile = 0x8;
DIR* dir;
struct dirent* entry;

if ( (dir = opendir (path.c_str())) != NULL) {

// print all the files and directories within directory
while ((entry = readdir (dir)) != NULL) {

if( (entry -> d_name)[0] == '.') 
{
	continue;
}

for( int i = 0; i < width; i++ ) 
{
	cout << "\t";
}

if( entry -> d_type == isFile ) 
{
	cout << entry -> d_name << " ";	
} 
else 
{
	cout << endl;
	cout << "./" << entry -> d_name << ":" << endl;
}
if( entry -> d_type == isDir ) 
{
	path += "/";
	path += entry -> d_name;
	print_default_dir( path, width + 1 );
}

}

closedir (dir);

} else 
{
	//could not open directory 
	cout << "Error: could not open directory." << endl;
	return;
}
}

int main(int argc, char** argv) 
{

if (argc > 1) 
{
	char *path = argv[1];
	struct stat buf;
	cin.ignore();

if ( stat(path, &buf) != -1 ) 
{
	if( S_ISREG(buf.st_mode) ) 
	{
		print_file( path, buf );
	} 
	else if( S_ISDIR(buf.st_mode) ) 
	{
		print_directory( path, 0 );
	}
	} 
	else 
	{
		cerr << "Error " << errno << " opening " << path << endl;
	}
	
	} 
	else 
	{
	
		string tmp = ".";
		print_default_dir(tmp,0);
	}

return 0;
}
