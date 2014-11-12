#include <iostream>
#include <fcntl.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <vector>



using namespace std;



void output(struct stat buf, dirent *direntp) 
{
    if(buf.st_mode & S_IXUSR)
    {
        cout<< direntp->d_name << " ";
    }   

    else if(buf.st_mode & S_IFDIR)
    {
        cout<< direntp->d_name << " ";
    }

    else if(direntp->d_name[0] == '.') 
    {
        cout<< direntp->d_name << " ";
    }   

    else if(direntp->d_name[0] == '.' && (buf.st_mode & S_IFDIR)) 
    {
        cout<< direntp->d_name << " ";
    }

    else if(direntp->d_name[0] == '.' && (buf.st_mode & S_IXUSR)) 
    {
        cout<< direntp->d_name << " ";
    }
    
    else
    {
        cout<<direntp->d_name << " ";
    }   
}

void printtime(const struct stat &buf)

{

    time_t t = buf.st_mtime;

    tm * tminfo = localtime(&t);

    char buffer[BUFSIZ]; 

    strftime(buffer, BUFSIZ, "%b %d %R", tminfo);

    cout << buffer << " "; 



}



void printall(const struct stat &buf) 

{



   if (buf.st_mode & S_IFREG) 
	cout<< "-";

    if(buf.st_mode & S_IFDIR)
	cout<< "d";

    if (buf.st_mode & S_IFLNK)
	cout<< "l";

    if (buf.st_mode & S_IFSOCK) 
	 cout<< "s";

    if (buf.st_mode & S_IFBLK) 
	cout<< "b";

    if (buf.st_mode & S_IFIFO) 
	cout<< "f";

    if (buf.st_mode & S_IFCHR) 
	cout<< "c";

    cout<<'-';





    //user

    cout<< " ";
    if (buf.st_mode & S_IRUSR) 
	cout << "r";
    else
	 cout << "-";

    if (buf.st_mode & S_IWUSR) 
	cout << "w";
    else
	 cout << "-";

    if (buf.st_mode & S_IXUSR) 
	cout << "x";
    else 
	 cout << "-";



    //group
    cout<< " ";

    if (buf.st_mode & S_IRGRP)  
	cout << "r"; 
    else
	cout << "-";

    if (buf.st_mode & S_IWGRP) 
	cout << "w"; 
    else
	cout << "-";

    if (buf.st_mode & S_IXGRP) 
	cout << "x";
    else
	cout << "-";



    //others
    cout<< " ";

    if (buf.st_mode & S_IROTH) 
	cout << "r";
    else
	cout << "-";

    if (buf.st_mode & S_IWOTH) 
	cout << "w";
    else
	 cout << "-";

    if (buf.st_mode & S_IXOTH) 
	cout << "x";
    else
	 cout << "-";





    cout << " ";

}


int noflag(string dirName) 

{

    if((strcmp(dirName.c_str(), "")) == 0)

    {

        dirName = "."; //default name

    }



    DIR *dirp;

    dirent *direntp;

    

    if(!(dirp = opendir(dirName.c_str()))) 

    {

        perror("opendir: ");

    }

    

    while ((direntp = readdir(dirp))) //readdir function, error checking inside loop

    {

        if(errno != 0)

        {

            perror("readdir");

        }

        

        struct stat buf;


        char filepath[1024];

        strcpy(filepath, dirName.c_str());

        strcat(filepath, "/");

        strcat(filepath, direntp->d_name);



        if((stat(filepath , &buf)) == -1) 

        {

            perror("stat: ");

        }

        

        if(direntp->d_name[0] == '.') //if the file name starts with a . continue on

        {

            continue;

        }


	output(buf, direntp);


    }

    

    cout << endl;

    

    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }

    

    return 0;

}

    

int aflag(string dirName) 

{ 

    if((strcmp(dirName.c_str(), "")) == 0)

    {

        dirName = ".";

    }

    

    

    DIR *dirp;

    

    dirent *direntp;

    



    if(!(dirp = opendir(dirName.c_str())))

    {

        perror("opendir: ");

    }

    

    while ((direntp = readdir(dirp)))

    {

        if(errno != 0)

        {

            perror("readdir");

        }

        

        struct stat buf;

        

        char filepath[1024];

        strcpy(filepath, dirName.c_str());

        strcat(filepath, "/");

        strcat(filepath, direntp->d_name);



        if((stat(filepath , &buf)) == -1)

        {

            perror("stat: ");

        }

        



    }

    

    cout << endl;

    

    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }



    return 0;

}






int lflag(string dirName)

{ 

    if((strcmp(dirName.c_str(), "")) == 0)

    {

        dirName = ".";

    }

    

    

    DIR *dirp;

    

    dirent *direntp;

    





    if(!(dirp = opendir(dirName.c_str())))

    {

        perror("opendir: ");

    }

    

    while ((direntp = readdir(dirp)))

    {

        if(errno != 0)

        {

            perror("readdir");

        }

        

        struct stat buf;

        char filepath[1024];

        strcpy(filepath, dirName.c_str());

        strcat(filepath, "/");

        strcat(filepath, direntp->d_name);



        if((stat(filepath , &buf)) == -1)

        {

            perror("stat: ");

        }

        

        struct passwd *pwd; 

        string userid;



        struct group *gid; 

        string groupid;



        int size = 0;



        if(direntp->d_name[0] == '.')

        {

            continue;

        }

        


        printall(buf); 

            


        cout << buf.st_nlink << " ";

        

        if(!(pwd = getpwuid(buf.st_uid)))

        {

            perror("getpwuid");

        }



        userid = pwd->pw_name;

        cout << userid << " ";

            


        if(!(gid = getgrgid(buf.st_gid)))

        {

            perror("getgrgid");

        }   

        

        groupid = gid->gr_name;

        cout << groupid << " ";   

            


        size = buf.st_size;

        cout << size << " ";

           


        printtime(buf); 





        cout << endl;

    }

    

    cout << endl;

    

    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }



    return 0;

}



int rflag(string dirName) 

{



    vector<char*> direc; 

    if((strcmp(dirName.c_str(), "")) == 0)

    {

        dirName = ".";

    }

    

    DIR *dirp;

    dirent *direntp;



    if(!(dirp = opendir(dirName.c_str())))

    {

	    perror("opendir");

    }

 

       

    if(strcmp(dirName.c_str(), ".") == 0)

    {

        cout << "." << endl;

    }

    

    else

    {

        cout << dirName << ":" << endl;

    }

    

    while ((direntp = readdir(dirp)))

    {

        if(errno != 0)

        {

            perror("readdir");

        } 

        

        struct stat buf;



        char filepath[1024];

        strcpy(filepath, dirName.c_str());

        strcat(filepath, "/");

        strcat(filepath, direntp->d_name);



        if((stat(filepath , &buf)) == -1)

        {

            perror("stat: ");

        }



        if ( direntp->d_name[0] == '.' )

        {

            continue;

        }



        

        if(S_ISDIR(buf.st_mode))

        {

		    direc.push_back(direntp->d_name); 

	    }



    }

    cout << endl;

    cout << endl;

 


    int dsize = direc.size();

    for(int d = 0; d < dsize; d++)

    { 

        rflag(dirName+"/"+ direc.at(d)); 

    }



    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }

    

    return 0;

}






int main(int argc, char *argv[])

{

    vector <char*> v;

    bool lflags = false, aflags = false, rflags = false;

    char* input; 

    string cinput = "";

    vector <string> in; 



    for(int i = 1; i < argc; i++) 

    {

        v.push_back(argv[i]);

    }



    int vsize = v.size(); 

    

    for(int d = 0; d < vsize; d++) 

    {

        if(strcmp(v.at(d), "-l") == 0) 

        {

            lflags = true;

        }



        else if(strcmp(v.at(d), "-a") == 0) 

        {

            aflags = true;

        }



        else if(strcmp(v.at(d), "-R") == 0) 

        {

            rflags = true;

        }

        

        else if((strcmp(v.at(d), "-la") == 0) || (strcmp(v.at(d), "-al") == 0))

        {

            lflags = true;

            aflags = true;

        }

        else if((strcmp(v.at(d), "-aR") == 0) || (strcmp(v.at(d), "-Ra") == 0))

        {

            rflags = true;

            aflags = true;

        }       

        else if((strcmp(v.at(d), "-lR") == 0) || (strcmp(v.at(d), "-Rl") == 0))

        {

            rflags = true;

            lflags = true;

        }



        

        else if((strcmp(v.at(d), "-alR") == 0) || (strcmp(v.at(d), "-aRl") == 0))

        {

            aflags = true;

            lflags = true;

            rflags = true;

        }

        else if((strcmp(v.at(d), "-laR") == 0) || (strcmp(v.at(d), "-lRa") == 0))

        {

            rflags = true;

            aflags = true;

            lflags = true;

        }

        else if((strcmp(v.at(d), "-Ral") == 0) || (strcmp(v.at(d), "-Rla") == 0))

        {

            rflags = true;

            aflags = true;

            lflags = true;

        }


        else 

        {

           input = v.at(d);

           cinput = string(input);

           in.push_back(cinput);

        }

    }

   

    int isize = in.size();




    if(!lflags && !aflags && !rflags)

    {

        if(isize>1)

        {

            for(int i = 0; i < isize; i++)

            {

                cout << in.at(i) << ":"<< endl;

                noflag(in.at(i));

                cout << endl;

            }

        }



        else

        {

            noflag(cinput);

        }

    }




    if(lflags && !aflags && !rflags)

    {

        if(isize>1)

        {

            for(int i = 0; i < isize; i++)

            {

                cout << in.at(i) << ":"<< endl;

                lflag(in.at(i));

                cout << endl;

            }

        }



        else

        {

            lflag(cinput);

        }

        

    }




    if(rflags && !aflags && !lflags)

    {

        if(isize>1)

        {

            for(int i = 0; i < isize; i++)

            {

                rflag(in.at(i));

                cout << endl;

            }

        }



        else

        {

            rflag(cinput);

        }

       

    }




    if(aflags && !lflags && !rflags)

    {

        if(isize>1)

        {

            for(int i = 0; i < isize; i++)

            {

                cout << in.at(i) << ":"<< endl;

                aflag(in.at(i));

         cout << endl;

            }

        }



        else

        {

         aflag(cinput);

        }

    }


}

