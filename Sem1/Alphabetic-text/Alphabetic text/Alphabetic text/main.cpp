#include <stdio.h>
#include <stdlib.h>
#include <Cocoa/Cocoa.h> // синтезатор речи
#include <cassert>

/*!
 \brief text mode constants
 */
enum mode {
    
    END_OF_LINE_MODE = '1', ///< end mode
    
    LINE_START_MODE = '0' ///< mode from the beginning
};



/*!
 \brief error constants
 */
enum program_errors {
    
    E_ERRORFUNCTION = -1, ///< error in function ErrorFunction()
    
    NO_ERROR = 0,         ///< no error
    
    E_PROCESSEDTEXT = 1,  ///< error in function ProcessedText()
    
    E_COUNTINGROWS = 2,   ///< error in function CountingRows()
    
    E_FILE_IN_MAIN = 3,   ///< error in function ReadFiles()
    
    E_PRINTFILES = 4      ///< error in function PrintFiles()
};




/*!
 \brief A structure that stores a pointer to the
 lines in the buffer and the length of the lines on the
 */
struct struct_text {
    int lenght;///< length of string
    char* str; ///< pointer to rows in an array
};

/*!
 \brief A structure that stores the names of two
 files that need to be processed and a sample for the main program test
 */
struct struct_arrey_test {
    char ordered [100];  ///< for check
    char unordered [100];///< for comparison
};


/*!
 \brief ReadFiles
 The function reads the text from the file into the buffer
 \param name_files write file name
 \param number_of_char variable for the number of characters
 \param error returns 4 if the file is empty
 \return Returns buffer
 */
char* ReadFiles (const char name_files [], long int *number_of_char, int* error);


/*!
 \brief PrintFiles
 This function print to file function
 \param name_files input file name
 \param text pointer to an array of structures, containing a string and its length
 \param number_of_lines lines number of elements in the array text
 \return Returns 0 if print was successful, 4 if file not found
 */
int PrintFiles(char name_files [], struct_text* text, const int number_of_lines);


/*!
 \brief PrintText
 Function displays text on the screen
 \param text pointer to an array of structures, containing a string and its length
 \param number_of_lines lines number of elements in the array text
 \return Returns 0
 */
int PrintText(struct_text* text, const int number_of_lines);


/*!
 \brief CountingRows
 Function counts the number of lines from the buffer
 \param file_valibation pointer to buffer
 \param number_of_lines pointer to the number of rows
 \param number_of_char pointer to the number of characters
 \return Returns 2 if there is no line, 0 if the search is successful
 */
int CountingRows (char* file_valibation, int* number_of_lines, long int* number_of_char);


/*!
 \brief CountingRows
 Fills an array of structures with pointers to the lines from the buffer and their length
 \param file_valibation pointer to buffer
 \param text pointer to an array of structures, containing a string and its length
 \param number_of_lines lines number of elements in the array text
 \return Returns 2 if there is no line, 0 if the search is successful
 */
int CreatMasText (char* file_valibation, struct_text* text, const int number_of_lines);


/*!
 \brief FindingWordsInLinesFromTheEnd
 Compares strings alphabetically from the end
 \param text1 pointer to an array of structures, containing a string and its length
 \param text2 pointer to an array of structures, containing a string and its length
 \return Returns 1 if text1 is older than text2 and -1 is reverse
 */
int FindingWordsInLinesFromTheEnd (const void* text1, const void* text2);


/*!
 \brief FindingWordsInStringsFromTheBeginning
 Compares strings alphabetically from the beginning
 \param text1 pointer to an array of structures, containing a string and its length
 \param text2 pointer to an array of structures, containing a string and its length
 \return Returns 1 if text1 is older than text2 and -1 is reverse
 */
int FindingWordsInStringsFromTheBeginning (const void* text1, const void* text2);


/*!
 \brief ProcessedText
 Formats the text
 \param text pointer to an array of structures, containing a string and its length
 \param number_of_lines lines number of elements in the array text
 \param mode file formatting mode
 \return Returns 1 if the mode is not specified correctly, 1 if the molding was successful
 */
int ProcessedText (struct_text* text, const int number_of_lines, const int mode);


/*!
 \brief ErrorFunction
 Shows errors in the program
 \param error error number
 \return Returns 0 if the function did not find errors
 */
int ErrorFunction (const int error);


/*!
 \brief UnityTest
 Function to test the text formatting algorithm
 \param name_files input file name
 \param test_files input file name
 \return Function returns 1 if the lines of the processed text do not match the pattern
 */
int UnitTest (const char name_files [], const char test_files []);


/*!
 \brief LineEquality
 Function to test the text formatting algorithm
 \param text pointer to an array of structures, containing a string and its length
 \param text_test pointer to an array of structures, containing a string and its length
 \param number_of_lines lines number of elements in the array text
 \return The function returns true if the strings match
 */
bool LineEquality (struct_text* text, struct_text* text_test, int number_of_lines);


/*!
 \brief TEST
 Test function of the program
 \return Return 1 if one or all tests are not executed
 */
int TEST();


/*!
 \brief SearchForCharacters
 Checks the character for being a letter
 \param strtext pointer to character
 \return Returns true if the character is a letter
 */
bool SearchForCharacters (const char* strtext);


/*!
 \author Kromov Alexey 713 MIPT
 
 Function reads the text from the file and prints it in three versions: in the original,
 according to the alphabet from the beginning of the lines, on the alphabet from the end of the lines.
 Prints these texts in files for further use by their user.
 */
int main()
{
    /*
    if (TEST()) {
        return 0;
    };
    */
    char name_files1 [] = "ReadText.txt";
    char name_files2 [] = "WriteTextABC.txt";
    char name_files3 [] = "WriteTextCBA.txt";
    int number_of_lines = 0, error = 0;
    long int number_of_char = 0;
    
    char* file_valibation = ReadFiles (name_files1, &number_of_char, &error);
    
    
    error = CountingRows (file_valibation, &number_of_lines , &number_of_char);
    
    
    struct_text text [number_of_lines];
    
    CreatMasText (file_valibation, text, number_of_lines);
    
    printf("Text from file: '%s'\n\n", name_files1);
    PrintText(text, number_of_lines);
    
    
    
    
    error = ProcessedText (text, number_of_lines, LINE_START_MODE);
    
    
    printf("\n\nProcessing of the text alphabetically from the beginning of the lines,\nprinting of the received text in a file: '%s'\n\n", name_files2);
    PrintText(text, number_of_lines);
    
    error = PrintFiles(name_files2, text, number_of_lines);
    
    
    
    
    error = ProcessedText (text, number_of_lines, END_OF_LINE_MODE);
    
    
    printf("\n\nProcessing of the text alphabetically from the end of lines,\nprinting of the received text in a file: '%s'\n\n", name_files3);
    PrintText(text, number_of_lines);
    
    error = PrintFiles(name_files3, text, number_of_lines);
    ErrorFunction (error);
    delete [] file_valibation;
    return 0;
}





char* ReadFiles (const char name_files [], long int *number_of_char, int* error) {
    assert (number_of_char);
    assert (error);
    
    FILE *files = fopen (name_files, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    fseek (files, 0, SEEK_END);
    *number_of_char = ftell(files);
    
    char* file_validation = new char [++*number_of_char];
    
    
    fseek (files, 0, SEEK_SET);
    fread (file_validation, sizeof (char), *number_of_char, files);
    fclose (files);
    file_validation [*number_of_char - 1] = '\0';
    return file_validation;
}




int PrintFiles(char name_files [], struct_text* text, const int number_of_lines) {
    assert(name_files != NULL);
    assert(text);
    assert(number_of_lines > 0);
    FILE *files = fopen (name_files, "wt");
    if (files == NULL)
    {
        return E_PRINTFILES;
    }
    for (int i = 0; i < number_of_lines; ++i) {
        fprintf (files, "%s\n", text[i].str);
    }
    
    fclose(files);
    return NO_ERROR;
}




int PrintText(struct_text* text, const int number_of_lines) {
    assert(text);
    assert(number_of_lines > 0);
    for (int i = 0; i < number_of_lines; ++i) {
        printf ("%i ) %s\n", i + 1, text[i].str);
        printf("\n");
    }
    return 0;
}




int CountingRows (char* file_validation, int* number_of_lines, long int* number_of_char) {
    assert(file_validation);
    assert(number_of_lines);
    assert(number_of_char);
    assert(*file_validation != NULL);
    for (int i = 0; i < *number_of_char; ++i) {
        if (file_validation[i] == '\n') {
            file_validation[i] = '\0';
            ++*number_of_lines;
        }
    }
    if (*number_of_lines < 1) {
        return E_COUNTINGROWS;
    }
    *number_of_char = *number_of_char - *number_of_lines + 2;
    file_validation[*number_of_char - 1] = '\0';
    return NO_ERROR;
}




int CreatMasText (char* file_validation, struct_text* text, const int number_of_lines) {
    assert(number_of_lines > 0);
    assert(text);
    assert(file_validation);
    assert(*file_validation != NULL);
    for (int i = 0, j = 0, k = 0; i < number_of_lines; ++i) {
        text[i].str = &file_validation [j];
        do {
            ++j;
            ++k;
        } while (file_validation [j] != '\0');
        text[i].lenght = k + 1;
        k = 0;
        ++j;
    }
    return 0;
}




int FindingWordsInLinesFromTheEnd (const void* text1, const void* text2) {
    
    const char* strtext1 = (*(struct_text*)text1).str + sizeof(char) * ((*(struct_text*)text1).lenght-1);
    const char* strtext2 = (*(struct_text*)text2).str + sizeof(char) * ((*(struct_text*)text2).lenght-1);
    const char* strtextstart1 = (*(struct_text*)text1).str;
    const char* strtextstart2 = (*(struct_text*)text2).str;
    
    
    do {
        while (SearchForCharacters (strtext1) && (strtext1 >= strtextstart1)) {
            --strtext1;
        }
        
        while (SearchForCharacters (strtext2) && (strtext2 >= strtextstart2)) {
            --strtext2;
        }
        
        while ((strtext2 >= strtextstart2) && (strtext1 >= strtextstart1) && ((int)*strtext1 == (int)*strtext2)) {
            --strtext1;
            --strtext2;
        }
    
    } while ((SearchForCharacters (strtext1) && (strtext1 >= strtextstart1)) && (SearchForCharacters (strtext2) && (strtext2 >= strtextstart2)));
    
    if (strtext1 < strtextstart1) {
        return E_ERRORFUNCTION;
    }
    
    if (strtext2 < strtextstart2) {
        return E_PROCESSEDTEXT;
    }
    
    if ((int)*strtext1 > (int)*strtext2) {
        return E_PROCESSEDTEXT;
    } else
    {
        return E_ERRORFUNCTION;
    }
}




bool SearchForCharacters (const char* strtext) {
    assert(strtext);
    return (((int)*strtext < 'A') || (((int)*strtext > 'Z') && ((int)*strtext < 'a')) || ((int)*strtext > 'z'));
}




int FindingWordsInStringsFromTheBeginning (const void* text1, const void* text2) {
    
    const char* strtext1 = (*(struct_text*)text1).str;
    const char* strtext2 = (*(struct_text*)text2).str;
    const char* strtextend1 = (*(struct_text*)text1).str + sizeof(char) * (*(struct_text*)text1).lenght;
    const char* strtextend2 = (*(struct_text*)text2).str + sizeof(char) * (*(struct_text*)text2).lenght;
    
    
    do {
        while (SearchForCharacters (strtext1) && (strtext1 <= strtextend1)) {
            ++strtext1;
        }
        
        while (SearchForCharacters (strtext2) && (strtext2 <= strtextend2)) {
            ++strtext2;
        }
        
        while ((strtext2 <= strtextend2) && (strtext1 <= strtextend1) && ((int)*strtext1 == (int)*strtext2)) {
            ++strtext1;
            ++strtext2;
        }
        
    } while ((SearchForCharacters (strtext1) && (strtext1 <= strtextend1)) && (SearchForCharacters (strtext2) && (strtext2 <= strtextend2)));
    
    if (strtext1 > strtextend1) {
        return E_ERRORFUNCTION;
    }
    
    if (strtext2 > strtextend2) {
        return E_PROCESSEDTEXT;
    }
    
    if ((int)*strtext1 > (int)*strtext2) {
        return E_PROCESSEDTEXT;
    } else
    {
        return E_ERRORFUNCTION;
    }
}




int ProcessedText (struct_text* text,const int number_of_lines,const int mode) {
    assert(number_of_lines > 0);
    assert(text);
    switch ( mode )
    {
        case LINE_START_MODE:
            qsort (text, number_of_lines, sizeof(struct_text), FindingWordsInStringsFromTheBeginning);
            break;
        case END_OF_LINE_MODE:
            qsort (text, number_of_lines, sizeof(struct_text), FindingWordsInLinesFromTheEnd);
            break;
        default:
            return E_PROCESSEDTEXT;
    }
    return NO_ERROR;
}




int ErrorFunction (const int error) {
    printf("\nstatus:\n");
    switch ( error )
    {
        case E_ERRORFUNCTION:
            assert (error != E_ERRORFUNCTION);
            break;
        case NO_ERROR:
            printf("\nOK\n");
            break;
        case E_PROCESSEDTEXT:
            printf("\nerror: ProcessedText()\n");
            assert (error != E_PROCESSEDTEXT);
            break;
        case E_COUNTINGROWS:
            printf("\nerror: CountingRows()\n");
            assert (error != E_COUNTINGROWS);
            break;
        case E_FILE_IN_MAIN:
            printf("\nerror: access to the file in main()\n");
            assert (error != E_FILE_IN_MAIN);
            break;
        case E_PRINTFILES:
            printf("\nerror: access to the file in PrintFiles()\n");
            assert (error != E_PRINTFILES);
            break;
        default:
            printf("Unknown error: %i", error);
            ErrorFunction (E_ERRORFUNCTION);
    }
    return 0;
}




int UnitTest (const char name_files [], const char test_files []) {
    
    int number_of_lines = 0, error = 0;
    long int number_of_char = 0;
    char* file_valibation_test = ReadFiles (test_files, &number_of_char, &error);
    
    error = CountingRows (file_valibation_test, &number_of_lines , &number_of_char);
    struct_text text_test [number_of_lines];
    CreatMasText (file_valibation_test, text_test, number_of_lines);
    
    
    
    number_of_lines = 0;
    number_of_char = 0;
    char* file_validation = ReadFiles (name_files, &number_of_char, &error);
    
    
    error = CountingRows (file_validation, &number_of_lines , &number_of_char);
    struct_text text [number_of_lines];
    CreatMasText (file_validation, text, number_of_lines);
    
    
    //error = ProcessedText (text, number_of_lines, line_start_mode);
    
    error = ProcessedText (text, number_of_lines, END_OF_LINE_MODE);
    
    
    if (LineEquality (text, text_test, number_of_lines)) {
        printf("\nerror test\n");
        return E_PROCESSEDTEXT;
    }
    
    printf("\nOK\n");
    ErrorFunction (error);
    return 0;
}




bool LineEquality (struct_text* text, struct_text* text_test, int number_of_lines) {
    assert(number_of_lines > 0);
    assert(text);
    for (int j = 0; j < number_of_lines; ++j) {
        for (int i = 0; i < text [j].lenght; ++i) {
            if ((text [j].str)[i] != (text_test [j].str)[i]) {
                printf("\nerror test\n");
                return true;
            }
        }
    }
    return false;
}




int TEST() {
    
    int TEST_error = 0;
    struct_arrey_test name_text [2] = {"Test11.txt\0","Test12.txt\0","Test21.txt\0","Test22.txt\0"};
    
    for (int i = 0; i < (sizeof(name_text) / sizeof(struct_arrey_test)); ++i) {
        
        printf("\n%i) test: ",i);
        
        
        TEST_error = UnitTest (name_text [i].ordered, name_text [i].unordered);
        
        if (TEST_error == E_PROCESSEDTEXT) {
            return E_PROCESSEDTEXT;
        }
        
    }
    printf("\n\n");
    return 0;
}

