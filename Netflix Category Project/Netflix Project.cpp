#include <iostream>
class CircularMovieList;
struct CategoryNodes;
using namespace std;

//this class is what stores the day of a movie and checks whether the date is valid
class MovieDayStorage{
public:
    int year;
    int month;
    int day;
    bool value; // Variable used to see if the date is acceptable or valid

    //Default Constructor
    MovieDayStorage(){}

    //Constructor with month, day, and year input
    MovieDayStorage(int month1, int day1, int year1){ //Creating a date that fits within the Gregorian calendar

        if ((month1 == 1 || month1 == 3 || month1 == 5 || month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12) && (day1 > 0 && day1 < 32)){ // These months have 31 days,
            //set your date and be done
            year = year1;
            month = month1;
            day = day1;
            value = true;
        }else if (month1 ==2 && day1 > 0 && day1 < 30){ //Checking for the month of Feburary
            //if your day in Feb is 29 and its not a leap year, then it's invalid
            if(day1 == 29 % year1 % 4 != 0){
                year = NULL; //If it's not a leap year and the attempted day is Feb 29thm, set year, month, day to NULL and value to false
                month = NULL;
                day = NULL;
                value = false;

            }else{
                year = year1; //If it's not the 29th, then you're good, so set your date
                month = month1;
                day = day1;
                value = true;
            }
        }

         else if ((day1 > 0 && day1 < 31) && (month1 == 4 || month1 == 6 || month1 == 9 || month1 == 11)){ //These months have 30 days
            year = year1; //if the day is valid in the month, then set the date
            month = month1;
            day = day1;
            value = true;
        }

        else{ //If none of the cases above is acceptable, the date can not be acceptable
            cout << "Date is not Valid";
        }

    }

    bool CheckMovieDate(MovieDayStorage inputDate){ //checking for the delete function whether a movie is before a date
        bool val;
        if (year < inputDate.year){ //If the year is before the inputDate year, then movie date is still acceptable
            val = true;
        }
        else if(year == inputDate.year){ // If the year is the same year as the inputDate year, need to check the month
            if(month < inputDate.month){ //If the month is before the inputDate month, then movie date is still acceptable
                val = true;
            }
            else if(month == inputDate.month){ // if the month is the same month as the inputDate month, need to check the day
                if (day < inputDate.day){ //If the day is before the inputDate day, then the movie date is still acceptable
                    val = true;
                }
                else{
                    val = false; //If day is equal or after the inputDate day, then the movie date is not acceptable
                }
            }
            else{
                val = false; //If the month is after the inputDate month, then the movie date is not acceptable
            }
        }
        else{
            val = false; //If the year is after the inputDate year, then the movie date is not acceptable
        }
        return val; // returning if the movie date is acceptable or not
    }

    void PrintDate(){
        if(value){ //If the date is fits within the calendar system, prints the date
            cout << month << " " << day << ", " << year << endl;
        }
        else{ //If the date does not fits within the calendar system, prints the following statement
            cout << "The date is not acceptable. Please input an acceptable date with the Gregorian calendar system" << endl;
        }
    }

};
//END OF MOVIE DATES CLASS


//These are the nodes for our movies
struct MovieNodes{
    string movieTitle; //Movie title
    MovieNodes* Next; //Points to the movie next in the linked list
    MovieNodes* Previous; // Point to the movies previous in the linked list
    bool isHead; //Check if the element is the 1st element (head) of the link list
    MovieDayStorage Date; //the date of our movie in the node

    MovieNodes(){}//default constructor

    //node constuctor
    MovieNodes(string title, MovieDayStorage MovieD){
        Date = MovieD;  //Setting date
        if (!Date.value){//If the date is not acceptable, print out statement
            cout << "Date is not acceptable";
        }
        //the node would end here if the date is not acceptable
        else{                           // if the date is acceptable, set title and pointers to NULL and head bool to false
            movieTitle = title;
            Next = NULL;
            Previous = NULL;
            isHead = false;
        }
    }


};

//these are jut nodes, not a list
struct CategoryNodes{
    string CategoryName; //Title of the category
    CategoryNodes* Next; //Points to the next element in the double link list
    CategoryNodes* Previous; //Points to the previous element in the double link list
    CircularMovieList* MovieList; //Will points to the movies in the circular movie link list

    //Default Constructor for the nodes
    CategoryNodes(){
    }

    CategoryNodes(string name){ //Constructor with variable for the Category Name
        MovieList = NULL;
        CategoryName = name;
        Previous = NULL;
        Next = NULL;

    }
};

//this is the list, which is a culmination of nodes
class CircularMovieList{
public:
    int numberOfMovies; //Counter for the amount of movies
    MovieNodes* Head; //Points to the first element of the list of movies
    MovieNodes* Tail; //Points to the last element of the list of movies

    //constructor
    CircularMovieList(){
        numberOfMovies = 0; //Setting amount of movies to zero
        Tail = NULL; //Point the tail and head to NULL
        Head = NULL;

    }

    int getnumberOfMovies(){ //Retrieve the number of movies
        return numberOfMovies;
    }

    MovieNodes* Gethead(){ //Retrieve the head of the list
        return Head;
    }

    MovieNodes* GetTail(){ //Retrieve the tail of the list
        return Tail;
    }


    //this function will add a movie to the movie list
     void AddMovie(string mn, MovieDayStorage moviedate){
         MovieNodes* temp = new MovieNodes(mn, moviedate); //Create a brand new node for MovieNode, with name and date

         if(Head == NULL){ //If our list is empty
             temp->isHead = true; //temp will become the head and tail

             Head = temp;
             Tail = temp;
             Tail->Next = Head; //Because its circular, the tail next pointer will point to the head
             Head->Previous = Tail; //Because its circular, the head previous pointer will point to the tail
             numberOfMovies += 1; // Increasing the counter
         }
         else{ //if the head already exists, or the linked list is NOT empty
             MovieNodes* current = Head; //Create Movie node and set it equal to head: this is just to compare nodes

             if(temp->movieTitle == Head->movieTitle){ // check if the movie title is the first element in the movie circular link list, if true, it doesn't change the list, but prints out that its in the list already
                 cout << temp->movieTitle << " is already in the list" << endl;
                 return;
             }
             for(current = Head->Next; current != Head; current = current->Next){ //This statement loops through the rest of the function until it reaches the head in a circle fashion
                 if(temp->movieTitle == current->movieTitle){ // checks if the movie title is the first element in the movie circular link list, if true, doesn't change the list, but prints out that its in the list already
                     cout << temp->movieTitle << " is already in the list" << endl;
                     return;
                 }
             }

             if(temp->movieTitle < Head->movieTitle){ //Inserting movie at the beginning of the list
                 temp->Next = Head; //Setting that temp is now head and it points next to the head
                 Head->isHead = false;
                 temp->isHead = true;
                 Head->Previous = temp; //the original head will now point previous to the temp
                 Head = temp; //Declaring that the temp is now head.
                 Head->Previous = Tail; //Because its circular, the tail next pointer will point to the head
                 Tail->Next = Head; //Because its circular, the head previous pointer will point to the tail
                 numberOfMovies += 1; // Increasing the counter
             }


             else{ //Inserting anywhere after the beginning of the link list
                 MovieNodes* current = Head; //Creating a node and setting it equal to head for comparison purposes

                 while(current->Next != Head && current->Next->movieTitle < temp->movieTitle){ //As long as the the current node does not point next to the head and movie title of the temp is greater than the next movie in the list (so we want to keep moving forward until we find it's place)
                     current = current->Next; // Moves the pointer to the next movie
                 }//once the condition is broken
                 temp->Next = current->Next; //Changing the pointers link list to accommodate a new movie in the link list
                 current->Next = temp;
                 temp->Next->Previous = temp;
                 temp->Previous = current;



                 if(temp->Next == Head){ //In the case the temp next points to the head, it means the temp is the last movie
                     Tail = temp; //Thus, tail has to be temp
                     Tail->Next = Head; //Tail has to point next to head
                 }
                 numberOfMovies += 1; //Increasing the counter
             }
         }
     }



    void deleteMovie(string T){
        if (Head == NULL){ //In the case the link list in empty already
            cout << "There are no movies in the list currently" << endl;
        }

        if (Head->movieTitle == T){ //This statement is for if  we want to delete the first movie in the link list
            Head->Next->isHead = true; //The 2nd movie becomes the 1st
            Head->Next->Previous = Tail; //The 2nd movie points previous to the tail
            Tail->Next = Head->Next; //The tail points to the 2nd movie
            Head = Head->Next; //Setting head as the 2nd movie
            //Basically just cutting out the 1st movie

            numberOfMovies = numberOfMovies - 1; //Decrease the counter
            return;
        }

        if(Tail->movieTitle == T){ //This statement is for if we want to delete the last move in the link list
            Tail->Previous->Next = Head; //The 2nd to last movie points next to the Head
            Head->Previous = Tail->Previous; //Head points previous to the 2nd to last movie
            Tail= Tail->Previous; //Setting the 2nd to last movie to the tail

            numberOfMovies = numberOfMovies - 1; // Decrease the counter
            return;
        }

        MovieNodes* current = Head;
        for (current = Head->Next; current->Next != Head;current = current->Next){ //Start at the 2nd element and loop through until it comes back to the head because it is a circular link list
            if (current->movieTitle == T){ //If the input title is equal to a title in the list
                current->Previous->Next = current->Next; //The previous movie will point to the current next...initially skipping over the current
                current->Next->Previous = current->Previous; // Vice versa to the logic above


                numberOfMovies = numberOfMovies - 1; // Decrease the counter
                return;
            }
        }

    }

    //print through all the movies
    void MoviePrint(MovieNodes* movieList){
        if(Head == NULL){ //If list is empty, prints out statement and return nothing
            cout << "The list is currently empty right now" << endl;
            return;
        }

        else{
            cout << movieList->movieTitle << "->"; //Prints out movies
            if(movieList->Next->isHead == true){ // If the list points back to the head, it means we have reached the end of the link list, does not print out the head and returns nothing
                cout << endl;
                return;
            }
            MoviePrint(movieList->Next); //Recursion to print over and over rather than use a for loop
        }
    }

};

//Double LL that ISN'T CIRCULAR for the categories
class CategoryDoubleLL{
private:
    CategoryNodes* Head = NULL; //Head pointer
    CategoryNodes* Tail = NULL; //Tail pointer
    int numCategories; //Counter for the number of categories

public:


    void AddingCategory(string n){ //Adding Category to the double link list

        CategoryNodes* Temp = new CategoryNodes(n); //Creating new node


        if (Head == NULL){ //Case in which there is no category

            Head = Temp; //Temps become the head and tail
            Tail = Temp;
        }

        else{ //If the category list is not empty, add the a new node to the end of the double link list
            Tail->Next = Temp; //Setting temp to the last movie
            Temp->Previous = Tail; //Temp points previous at the tail
            Tail = Temp; //declaring that the temp is now the tail

        }
        numCategories = numCategories + 1; // Increase the counter
    }




    void removingCategory(string n){//Deleting a node from the Category List -----There are four separate cases.

        if (Head == NULL){ //If the double link list that represent that movie list is empty, nothing can be removed
            cout << "The Category List is empty currently" << endl;
            return;
        }

        if(Head->CategoryName == n){ //If you want to remove the first element in double link list
             Head = Head->Next; //2nd movie becomes the 1st movie
             numCategories = numCategories -1;
             cout << "success" << endl; //Decreasing counter
            return;
        }

        if (Tail->CategoryName == n){ //If you want to remove the last element in double link list
            Tail = Tail->Previous; //2nd to last movie becomees the tail
            Tail->Next = NULL; //New tail points next to nothing
            numCategories = numCategories -1; //Decreasing counter
            cout << "success" << endl;
            return;
        }

        CategoryNodes* current = Head; //Creating a pointer that points to Head
        for(current = Head->Next; current->Next != NULL; current = current->Next){ //Loop through the rest of the category
            if (current->CategoryName == n){ //If you want to remove an middle element in double link list
                current->Previous->Next = current->Next; //The movie behind the current points to the current next...initilazing skipping current
                current->Next->Previous = current->Previous; // Vice versa logic from above


                numCategories = numCategories -1; //Decreasing counter
                cout << "success" << endl;
                return;
            }

        }
        cout << "failure" << endl;
    }

    CategoryNodes* CategorySearch(string NameCategory){
        CategoryNodes* current = Head; // Create pointers that is set to the Head

        for (current = Head; current != NULL; current = current->Next){//Looping through the categories u
            if(current->CategoryName == NameCategory){ //If category matches the input category, it will return the Category node
                cout << NameCategory << " is a category found" << endl;
                return current;
            }
        }
        cout << NameCategory << " was not found"<< endl; //After looping everything and nothing is found, it will return NULL
        return NULL;
    }

     void AddMovietoCat(string t, string category1, MovieDayStorage date){ //Adding a movie to a specific category
         CategoryNodes* currentC = CategorySearch(category1); //Need to make sure the category exist in the list

         if(currentC == NULL){ // After search function, it currentC is Null, does not exist
             cout << "This category does not exist" << endl;
             return;
         }

         if(currentC->MovieList == NULL){ // In the case that the category does not points to anything, it will create a new circular link list for the category
             currentC->MovieList = new CircularMovieList();
         }

         currentC->MovieList->AddMovie(t, date); //Adding the movie to the link list by calling AddMovie function
         cout << "movie " << t << " added" << endl;
     }


    void PrintMovsinCategory(CategoryNodes* Category){
        if(Category == NULL){ //If the Category is empty or doesn't exist, print statement
            cout << "There is no category and thus no movies within the nonexistant category" << endl;
            return;
        }
        else{
            cout << "Category: " << Category->CategoryName << "--> Movies: "; //Prints the category
            Category->MovieList->MoviePrint(Category->MovieList->Gethead());//Print the movies in the category
        }
    }

    int MovieCategoryBinarySearch(string movTitle, CategoryNodes* Category, int high, int low){ //Implementing a Binary search for a category
        bool value; //Create bool variable
        int middle; //Create a variable for the middle of the link list
        MovieNodes* getToMiddle = Category->MovieList->Gethead();

        if (Category->MovieList == NULL){ //Can not do a binary search if the list is point to NULL (is empty)
            cout << "Category is not avaliable at this time" << endl;
            return false ;
        }

        if (low > high){ //If the low value is greater than the high value, its does not make sense and binary search will not occur, thus can not find the movie
            value = false;
        }
        else{                   //Binary search condition is met and can occur
            middle = (low + high) / 2; //Finding the middle element of the link list


            for (int j = 0; j < middle; j++){ //Using a while loop to push the getToMiddle pointer variable to the middle of the link list
                getToMiddle = getToMiddle->Next;
            }
            if(getToMiddle->movieTitle == movTitle){ // Base case for recursive function: If the movie is at the middle, movie is found
                value = true;
            }
            else{
                if (getToMiddle->movieTitle > movTitle){ //If the movie title is in the lower half of the list
                    value = MovieCategoryBinarySearch(movTitle, Category, high, middle + 1) ; //Recursive function
                }
                else{       //if the movie title is in the upper half of the list
                    value = MovieCategoryBinarySearch(movTitle, Category, middle - 1, low); //Recursive function
                }
            }
        }
        return value; //return the bool value
    }

    int getMovieIndex(string t, CategoryNodes* Category){

        if (Category->MovieList == NULL){ // If the the category points to a empty movie list
            return 0;
        }
        else{
            MovieNodes* current = Category->MovieList->Gethead(); //Set pointer to the be the head of the movie list

            for (int num = 0; num < Category->MovieList->getnumberOfMovies(); num++){ //Loop through the movie list
                if (current->movieTitle == t){ //If at an index movie is equal to the input title
                    cout << t << "'s index in the Circular Movie Link List: " << num << endl;
                    return num; //Need to return num since this function is an int function
                }
                current = current->Next; //Moves to the next Category
            }
            cout << "Movies does not exist in Category" << endl;
            return 0;
        }
    }


   bool SearchingAllMovies(string t){
        CategoryNodes* currentC = Head; //Create pointer that points the Head of the category list

        while(currentC != NULL){ //Looping through all the categories
            if(MovieCategoryBinarySearch(t, currentC, currentC->MovieList->getnumberOfMovies(), 0)){ //Search through the movies at each categories via Binary Search
                cout << "The movie, " << t << ", was located in the " << currentC->CategoryName << " Category" << endl; //If it is found, cout a statement
                return true; //Because bool function need to return a bool value
            }
            currentC = currentC->Next; //Moves on to the next category
        }
        cout << "The movie, " << t << ", was not located at all" << endl;
        return false; //Because bool function need to return a bool value
    }



    void AllMoviesPrint(){

        CategoryNodes* elems = Head; //Create Node that is equal to the Head (first category)
        while(elems != NULL){ //Looping through all the cateogries
            PrintMovsinCategory(elems); //Printing Movies in each Category
            elems = elems->Next; //Moving on to the next category
        }
    }


    void beforeDueDateDelete(MovieDayStorage date){
        CategoryNodes* currentC = Head; //Create pointer for category and set to Head
        MovieNodes* currentM; //Create pointer for movies
        for(currentC = Head; currentC != NULL; currentC = currentC->Next){ //Loop through categories and then points to next category
            if (currentC->MovieList->Gethead()->Date.CheckMovieDate(date)){
                cout << "The following movie have been deleted from the list: " << currentC->MovieList->Gethead()->movieTitle << endl;
                currentC->MovieList->deleteMovie(currentC->MovieList->Gethead()->movieTitle);
            }
            for (currentM = currentC->MovieList->Gethead()->Next; !currentM->isHead; currentM = currentM->Next){ //Loop through movies category
                if(currentM->Date.CheckMovieDate(date)){
                    cout << "The following Movie have been deleted from the list: " << currentM->movieTitle << endl;
                    currentC->MovieList->deleteMovie(currentM->movieTitle);
                }
            }
        }
    }


};



int main(){

    CategoryDoubleLL Netflix;



// USER INPUT
bool useAgain = true;
while(useAgain == true){
    int input = 0;
    cout << "please enter an input for the operator you wish:" << endl;
    cout << "1: Add category" << endl << "2: add movie to category" << endl << "3: Print all Movies" << endl << "4: Search for a movie" << endl;
    cout << "5: Delete a category" << endl << "6: Binary Search a Movie in a Category" << endl << "7: Find Movie Index" << endl << "8: Print all Movies in Category" << endl;
    cout << "9: Search For a Category" << endl << "10: delete all movies before a date" << endl;

    cin >> input;
    switch(input){
    //case for adding a new category: we have to check for dupes
    case 1:
    {
        cout << "please input the name of the category you wish to add" << endl;
        string categoryAdded;
        cin >> categoryAdded;
        if(Netflix.CategorySearch(categoryAdded) == NULL){
            Netflix.AddingCategory(categoryAdded);
            cout << "category added" << endl;
        }else{
        cout << "duplicate category: try again!" << endl;
        }
        break;
    }

    case 2:
    {
       cout << "input the name of the category you want the movie to be added to" << endl;
       string categoryName;
       cin >> categoryName;
       cout << "please input name of movie" << endl;
       string movieName;
       cin >> movieName;
       cout << "please input date in the format M D Y"<< endl;
       int month;
       int day;
       int year;
       cin >> month >> day >> year;
       Netflix.AddMovietoCat(movieName, categoryName, MovieDayStorage(month, day, year));
       break;
    }
    case 3:
    {
            Netflix.AllMoviesPrint();
            break;
    }
    case 4:
    {
        cout << "input name of movie to search for" << endl;
        string movieName;
        cin >> movieName;
        Netflix.SearchingAllMovies(movieName);
        break;

    }
    case 5:
    {
        cout << "input name of category to be deleted" << endl;
        string categoryName;
        cin >> categoryName;
        Netflix.removingCategory(categoryName);
        break;
    }

    case 6:
    {
        string BinSearchMovie;
        cout << "Insert movie to search for via Binary Search" << endl;
        cin >> BinSearchMovie;
        string BinSearchCat;
        cout << "Insert Category to search for" << endl;
        cin >> BinSearchCat;
        cout << "Searching for movie " << BinSearchMovie << " in category " << BinSearchCat << endl;
    if(!Netflix.MovieCategoryBinarySearch(BinSearchMovie,Netflix.CategorySearch(BinSearchCat), Netflix.CategorySearch(BinSearchCat)->MovieList->getnumberOfMovies(), 0)){
        cout << BinSearchMovie << " was found in " << BinSearchCat << " via binary search" << endl;
    }
    else{
        cout << BinSearchMovie << " not was found"  << endl;
    }

        break;
    }
    case 7:
    {
        cout << "Insert movie name" << endl;
        string MovieIndexMov1;
        cin >> MovieIndexMov1;
        string MovieIndexCat1;
        cout << "Insert category you want to search in" << endl;
        cin >> MovieIndexCat1;
        Netflix.getMovieIndex(MovieIndexMov1, Netflix.CategorySearch(MovieIndexCat1));

        break;
    }
    case 8:
    {
        string printMovCat1;
        cout << "Insert category to print" << endl;
        cin >> printMovCat1;
        cout << "Printing movies in " << printMovCat1 << " category" << endl;
        Netflix.PrintMovsinCategory(Netflix.CategorySearch(printMovCat1));
        break;
    }
    case 9:
    {
        string SearchCatName1;
        cout << "Insert category to search for" << endl;
        cin >> SearchCatName1;
        Netflix.CategorySearch(SearchCatName1);

        break;
    }
    case 10:
    {
        int DueDateMonth, DueDateDay, DueDateYear;
        cout << "Insert due date (M D Y)" << endl;
        cin >> DueDateMonth >> DueDateDay >> DueDateYear;

        cout << "Deleting Movies before " << DueDateMonth << " " << DueDateDay << ", " << DueDateYear << endl;
        Netflix.beforeDueDateDelete(MovieDayStorage(DueDateMonth, DueDateMonth, DueDateYear));
        break;
    }


    default:
        cout << "invalid case" << endl;

    }


    cout << endl << endl << endl << "use again? (y/n)";
    string YesorNo;
    cin >> YesorNo;
    if(YesorNo == "y"){


    }else{
        useAgain = false;
    }

}

cout << endl << endl << endl << "Goodbye!";



    //HARD CODE FOR TESTING

    /*Netflix.AddingCategory("Action"); //Adding Category Function
    Netflix.AddingCategory("TVShows");
    Netflix.AddingCategory("Anime");
    Netflix.AddingCategory("Kdrama");

    Netflix.AddMovietoCat("Contractor", "Action", MovieDates(4,1,2022)); //Adding movies to category in alphabetic order function
    Netflix.AddMovietoCat("Batman", "Action", MovieDates(3,4,2022));
    Netflix.AddMovietoCat("Aquaman", "Action", MovieDates(12,21,2018));
    Netflix.AddMovietoCat("Superman", "Action", MovieDates(6,17,1983));
    Netflix.AddMovietoCat("Venom", "Action", MovieDates(11,9,2018));

    //action category
    Netflix.AddMovietoCat("Friends", "TVShows", MovieDates(9,22,1994));
    Netflix.AddMovietoCat("Suits", "TVShows", MovieDates(6,23,2011));
    Netflix.AddMovietoCat("Brooklyn99", "TVShows", MovieDates(9,17,2013));
    Netflix.AddMovietoCat("BBT", "TVShows", MovieDates(9,24,2007));
    Netflix.AddMovietoCat("Sheldon", "TVShows", MovieDates(9,25,2017));

    // comedy category
    Netflix.AddMovietoCat("Horimiya", "Anime", MovieDates(1,10,2021));
    Netflix.AddMovietoCat("Kuroko", "Anime", MovieDates(4,7,20012));
    Netflix.AddMovietoCat("Haikyuu", "Anime", MovieDates(4,6,2014));
    Netflix.AddMovietoCat("YourName", "Anime", MovieDates(8,26,2017));

    //Kdrama category
    Netflix.AddMovietoCat("Vagabond", "Kdrama", MovieDates(9,20,2019));
    Netflix.AddMovietoCat("CrashLandingOnYou", "Kdrama", MovieDates(12,14,2019));


    cout << "****TESTING FUNCTIONS*****" << endl;

    cout << "PRINTING ALL MOVIES OF ALL CATEGORIES" << endl;
    Netflix.AllMoviesPrint();
    cout << endl;


    cout << "SEARCHING A MOVIE BY NAME" << endl;
    string SearchMovName1 = "Friends";
    Netflix.SearchingAllMovies(SearchMovName1);
    string SearchMovName2 = "Life";
    Netflix.SearchingAllMovies(SearchMovName2);
    cout << endl << endl;


    cout << "DELETING CATEGORY BY NAME" << endl;
    cout << "Insert Category to be delete: ";
    string deleteCatName1 = "TVShows";
    Netflix.removingCategory(deleteCatName1);
    cout << "Printing all movies of all categories after " << deleteCatName1 << " is deleted" << endl;
    Netflix.AllMoviesPrint();
    cout << endl << endl;


    cout << "BINARY SEARCH" << endl;
    string BinSearchMovie = "Superman";
    cout << "Insert movie to search for via Binary Search: " << BinSearchMovie << endl;
    string BinSearchCat = "Action";
    cout << "Insert Category to search for: " << BinSearchCat << endl;
    cout << "Testing Binary Search" << endl;
    if(!Netflix.MovieCategoryBinarySearch(BinSearchMovie,Netflix.CategorySearch(BinSearchCat), Netflix.CategorySearch(BinSearchCat)->MovieList->gNumMovies(), 0)){
        cout << BinSearchMovie << " was found in " << BinSearchCat << " via binary search" << endl;
    }
    else{
        cout << BinSearchMovie << " not was found"  << endl;
    }
    cout << endl << endl;


    cout << "FINDING MOVIE INDEX" << endl;
    string MovieIndexMov1 = "YourName";
    string MovieIndexCat1 = "Anime";
    Netflix.getMovieIndex(MovieIndexMov1, Netflix.CategorySearch(MovieIndexCat1));
    string MovieIndexMov2 = "Batman";
    string MovieIndexCat2 = "Action";
    Netflix.getMovieIndex(MovieIndexMov2, Netflix.CategorySearch(MovieIndexCat2));
    cout << endl << endl;

    cout << "PRINTING ALL MOVIES IN TWO DIFFERENT CATEGORY" << endl;;
    string printMovCat1 = "Anime";
    cout << "Printing movies in " << printMovCat1 << " category" << endl;
    Netflix.PrintMovsinCategory(Netflix.CategorySearch(printMovCat1));

    cout << endl;
    string printMovCat2 = "Action";
    cout << "Printing movies in " << printMovCat2 << "category" << endl;
    Netflix.PrintMovsinCategory(Netflix.CategorySearch(printMovCat2));
    cout << endl << endl;

    cout << "**********REQUIRES USER INPUT**********" << endl << endl;

    cout << "SEARCHING A CATEGORY BY NAME" << endl;
    string SearchCatName1;
    cout << "Insert Category that exist in Netflix: ";
    cin >> SearchCatName1; //Test category name that exist in Netflix
    Netflix.CategorySearch(SearchCatName1);
    cout << Netflix.CategorySearch(SearchCatName1)->CategoryName << " does exist in Netflix" << endl;
    string SearchCatName2;
    cout << "Insert Category that does not exist in Netflix: ";
    cin >> SearchCatName2; //Test category name that does not exist in Netflix
    Netflix.CategorySearch(SearchCatName2);
    cout << endl << endl;

    cout << "DELETING ALL MOVIES BEFORE A DATE" << endl;
    int DueDateMonth, DueDateDay, DueDateYear;
    cout << "Insert due date to delete all movies by (Month, Day, Year): " << endl;
    cin >> DueDateMonth >> DueDateDay >> DueDateYear;
    cout << "Deleting Movies before " << DueDateMonth << " " << DueDateDay << ", " << DueDateYear << endl;
    Netflix.beforeDueDateDelete(MovieDates(DueDateMonth, DueDateMonth, DueDateYear));
    cout << "Movies produced after " << DueDateMonth << " " << DueDateDay << ", " << DueDateYear << ": " << endl;
    Netflix.AllMoviesPrint();
    cout << endl << endl;*/


    return 0;
}

