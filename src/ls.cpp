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





void printtime(const struct stat &buf) //prints the time

{

    time_t t = buf.st_mtime;

    tm * tminfo = localtime(&t);

    char buffer[BUFSIZ]; 



    strftime(buffer, BUFSIZ, "%b %d %R", tminfo);

    cout << buffer << " "; 



}



void printall(const struct stat &buf) //prints the mode, then prints read, write, execute permissions

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


int noflag(string dirName) //this function is for when the user inputs no flags

{

    if((strcmp(dirName.c_str(), "")) == 0) //if user did not specify a file/directory

    {

        dirName = "."; //default name

    }



    DIR *dirp;

    dirent *direntp;

    



    if(!(dirp = opendir(dirName.c_str()))) //opendir and error checking

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

        //modify the directory name so that it's usable, append on the necessary parts

        char filepath[1024];

        strcpy(filepath, dirName.c_str());

        strcat(filepath, "/");

        strcat(filepath, direntp->d_name);



        if((stat(filepath , &buf)) == -1) //stat function & error checking

        {

            perror("stat: ");

        }

        

        if(direntp->d_name[0] == '.') //if the file name starts with a . continue on

        {

            continue;

        }



        //filename

        //cout << direntp->d_name << " ";

        //output(buf, direntp);

    }

    

    cout << endl;

    

    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }

    

    return 0;

}

    

int aflag(string dirName) //this function is for when the user inputs ONLY the -a flag

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

        


    //note there is no continue here, as we want the . files

    }

    

    cout << endl;

    

    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }



    return 0;

}





// for just the l-flag

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

        

        struct passwd *pwd; //used later to get user id

        string userid;



        struct group *gid; //used later to get group id

        string groupid;



        int size = 0;



        if(direntp->d_name[0] == '.')

        {

            continue;

        }

        

        //have to print out extra info for the -l flag



        //prints mode and file permissions

        printall(buf); 

            

        //number of links

        cout << buf.st_nlink << " ";

        

        if(!(pwd = getpwuid(buf.st_uid)))

        {

            perror("getpwuid");

        }



        userid = pwd->pw_name;

        cout << userid << " ";

            

        //gid

        if(!(gid = getgrgid(buf.st_gid)))

        {

            perror("getgrgid");

        }   

        

        groupid = gid->gr_name;

        cout << groupid << " ";   

            

        //size in bytes

        size = buf.st_size;

        cout << size << " ";

           

        //month, date, time

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



int rflag(string dirName) //this is for recursion, where the user inputs -R

{



    vector<char*> direc; //vector that will store directory names for recursion	

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

        cout << ".:" << endl;

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

 

    //this is the recursive portion

    int dsize = direc.size();

    for(int d = 0; d < dsize; d++) //for each directory in the vectory, call rflag again

    { 

        rflag(dirName+"/"+ direc.at(d)); //append the necessary parts so that it can be called

    }



    if((closedir(dirp)) == -1)

    {

        perror("closedir: ");

    }

    

    return 0;

}






int main(int argc, char *argv[])

{

    vector <char*> v; //this will contain everything the user inputs

    bool lflags = false, aflags = false, rflags = false;

    char* input; //the char and string will help keep track of files/directories

    string cinput = "";

    vector <string> in; //this will contain all the files/directories the user inputs



    for(int i = 1; i < argc; i++) //gathers user input into a vector, starts at 1 so it does not include ./ls 

    {

        v.push_back(argv[i]);

    }



    int vsize = v.size(); //size of vector

    

    for(int d = 0; d < vsize; d++) //time to check every element in the vector

    {

        if(strcmp(v.at(d), "-l") == 0) //if user has enetered -l

        {

            lflags = true;

        }



        else if(strcmp(v.at(d), "-a") == 0) //-a

        {

            aflags = true;

        }



        else if(strcmp(v.at(d), "-R") == 0) //-R

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

        //this is if there is something in the input that isn't any of the flags. this means it is either a file/directory

        else //or invalid input

        {

           input = v.at(d);

           cinput = string(input);

           in.push_back(cinput);

        }

    }

   

    int isize = in.size();

    //previous part was checking for flags & file/directory, now we call the functions based on the user input



    //no flags

    if(!lflags && !aflags && !rflags)

    {

        if(isize>1)//if there is more than one file or directory

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



    //-l flag only

    if(lflags && !aflags && !rflags)

    {

        if(isize>1)//if there is more than one file or directory

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



    //-rflag only

    if(rflags && !aflags && !lflags)

    {

        if(isize>1)//if there is more than one file or directory

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



    //-a flag only

    if(aflags && !lflags && !rflags)

    {

        if(isize>1)//if there is more than one file or directory

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
