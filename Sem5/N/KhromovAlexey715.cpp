//
//  main.cpp
//  N
//
//  Created by macbook on 18.11.2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cassert>
#include <unistd.h>
#include <sys/stat.h>


#define ASSERT_MAT( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_MATH=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}


#define SuperPuperDeBUG(vol)\
//vol;



template <typename data_t>
class Vector;

template <typename data_t>
class subMatrix {
    int size_;
    data_t* data_;
public:
    
    subMatrix (int size)
    {
        size_ = size;
        data_ = new data_t [size_] {};
        ASSERT_MAT(data_ != NULL)
        
    }
    ~subMatrix()
    {
        delete [] data_;
    }
    
    data_t get (int y) const;
    data_t& set (int y);
    
    data_t& operator [] (int i);
    
};




template <typename data_t>
class Matrix {
    int size_;
    
    subMatrix<data_t>** data_;
    
public:
    Matrix ();
    Matrix (int size);
    Matrix (Matrix& M);
    ~Matrix ();
    
    int getsize() {
        return size_;
    }
    
    Matrix<data_t> T ();
    
    
    data_t det(int size = -1);
    bool nondegeneracy();
    bool positive();
    bool symmetry();
    
    int SubMatrixDet(int ni, int nj, Matrix<data_t> &M, int size = -1);
     
    
    subMatrix<data_t>& operator [] (int i);
    

    int BufToMatrix (char* buf);
    
    template <typename data_t1>
    friend std::ostream& operator<< (std::ostream &out, Matrix<data_t1> &M);
    template <typename data_t1>
    friend std::istream& operator>> (std::istream &in, Matrix<data_t1> &M);
    
    Matrix& operator = (const Matrix& A);
    Matrix& operator = (data_t x);
    //*
   
    
    
    bool operator == (const Matrix& A);
    bool operator != (const Matrix& A);
    
    template <typename data_t1>
    friend bool operator == (Matrix<data_t1>& A, Matrix<data_t1>& B);
    
    template <typename data_t1>
    friend Vector <data_t1> operator * (Matrix<data_t1>& A, Vector<data_t1>& B);
    //*
    
};

template <typename data_t>
class Vector {
    int size_;
    
    data_t* data_;
    
public:
    Vector ();
    Vector (int size);
    Vector (Vector& V);
    ~Vector ();
    
    data_t& operator [] (int i);
    
    double abc ();
    
    
    int getsize() {
        return size_;
    }
    
    template <typename data_t1>
    friend std::ostream& operator<< (std::ostream &out, Vector<data_t1> &V);
    template <typename data_t1>
    friend std::istream& operator>> (std::istream &in, Vector<data_t1> &V);
    
    Vector& operator = (const Vector& A);
    Vector& operator = (data_t x);
    //*
    template <typename data_t1>
    friend Vector<data_t1> operator - (Vector<data_t1>& A, Vector<data_t1>& B);
    
    
    template <typename data_t1>
    friend Vector <data_t1> operator * (Matrix<data_t1>& A, Vector<data_t1>& B);
    //*
    
};



char *Read_File_To_Buffer(const char *name, int *state_func, bool UNIX = false);

FILE *open_file(const char *name, unsigned long *file_size, bool UNIX);



int SearchLU (Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, int SIZE);

int SolutionLU(Vector<double> &b, Vector<double> &x, Matrix<double> &A, int SIZE);



int main(int argc, const char * argv[]) {
    
    const char *name = argv[1];
    
    SuperPuperDeBUG(printf("%s\n",argv[1]))
    

    int state_func_ReadFile = 0;
    char *buf = Read_File_To_Buffer(name, &state_func_ReadFile);
    if (buf == nullptr) {
        printf("\n" "it's very bad!! ERROR in Read_File_To_Buffer: %d\n", state_func_ReadFile);
        return 1;
    }
    
    int SIZE = buf [0] - '0';
    
    Matrix<double> A (SIZE);
    Matrix<double> I (SIZE);
    Vector<double> F (SIZE);
    Vector<double> u (SIZE);
    Vector<double> x (SIZE);
    double epsilon = 0.000001;
    double r = epsilon * 2;
    
    
    A.BufToMatrix(buf);
    free(buf);
    SuperPuperDeBUG(std::cout << "A = \n" << A << std::endl)
    
    
    
    if (!(A.symmetry())) {
        printf("\n" "it's very bad!! ERROR the matrix A is asymmetric!\n");
        return 1;
    }
    if (!(A.positive())) {
        printf("\n" "it's very bad!! ERROR the matrix A is not positive!\n");
        return 1;
    }

    I = A;
    
    for (int i = 0; i < SIZE; i++) {
        F [i] = F [i] - exp(- u [i]);
        I [i] [i] = A [i] [i] + exp(- u [i]);
    }
    
    
    for (int s = 0; r > epsilon; s++) {
        
        
        SuperPuperDeBUG(std::cout << "F = \n" << F << std::endl)
        SuperPuperDeBUG(std::cout << "I = \n" << I << std::endl)
        
        if (SolutionLU(F, x, I, SIZE) == -1) {
            printf("it's very very very bad!!");
            return 0;
        }
        
        u = u - x;
        F = A * u;
        for (int i = 0; i < SIZE; i++) {
            F [i] = F [i] - exp(- u [i]);
            I [i] [i] = A [i] [i] + exp(- u [i]);
        }
        r = F.abc();
        
        printf("Iteration number %i: Residual rate = %lg\n", s, r);
        std::cout << "u = \n" << u << std::endl;
    }
    
    return 0;
}




int SolutionLU(Vector<double> &b, Vector<double> &x, Matrix<double> &A, int SIZE) {
    
    
    Matrix<double> L (SIZE);
    Matrix<double> U (SIZE);
    Vector<double> y (SIZE);
    
    
    if (SearchLU(A, L, U, SIZE) == -1) {
        printf("it's very very bad!!");
        return -1;
    }
    
    for (int i = 0, sum = 0; i < SIZE; i++, sum = 0) {
        for (int j = 0; j < i; j++) {
            sum += y [j] * L [i] [j];
        }
        y [i] = b [i] - sum;
    }
    
    for (int i = SIZE - 1, sum = 0; i >= 0; i--, sum = 0) {
        for (int j = SIZE - 1; j > i; j--) {
            sum += x [j] * U [i] [j];
        }
        x [i] = (y [i] - sum) / U [i] [i];
    }
    
    return 0;
}




int SearchLU (Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, int SIZE) {
    
    
    if (!(A.nondegeneracy())) {
        printf("it's very bad!! ERROR: 1\n");
        return 0;
    }
    //*
    if (A [0] [0] == 0) {
        printf("it's very bad!! ERROR: 2\n");
        return 0;
    }
    //*/
    U = A;
    
    
    
    for (int i = 0; i < SIZE; i++)
        for (int j = i; j < SIZE; j++)
            L [j] [i] = U [j] [i] / U [i] [i];
    
    for (int k = 1; k < SIZE; k++)
    {
        for (int i = k - 1; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                L [j] [i] = U [j] [i] / U [i] [i];

        for (int i = k; i < SIZE; i++)
            for (int j = k - 1; j < SIZE; j++)
                U [i] [j] = U [i] [j] - L [i] [k - 1] * U [k - 1] [j];
    }
    
    SuperPuperDeBUG(std::cout << "L = \n" << L << std::endl)
    SuperPuperDeBUG(std::cout << "U = \n" << U << std::endl)
    /*
    Matrix<double> LU (SIZE);
    LU = L * U;
    
    if (A != LU) {
        printf("it's very bad!! ERROR: 3\n");
        SuperPuperDeBUG(std::cout << "A = \n" << A << std::endl)
        SuperPuperDeBUG(std::cout << "A = LU =\n" << LU << std::endl)
        return -1;
    }
    //*/
    return 0;
}



FILE *open_file(const char *name, unsigned long *file_size, bool UNIX = false) {
    // Размер файла выдаётся в байтах
    // --------------------------------------------------------------------
    // В системе UNIX можно сделать проверку на существование и на
    // доступность чтения данного файла перед тем, как его открыть, и при
    // помощи fseek и ftell узнать размер файла (Переменной UNIX передать true).
    // Но для кроссплатформенности нужно использовать fstat (UNIX == false)
    // То есть: !(UNIX) => UNIX == false
    // --------------------------------------------------------------------

    assert(name != nullptr);
    assert(file_size != nullptr);

    FILE *file = nullptr;

    if (UNIX) { // Узнаём размер будучи в ОС на UNIX
        if (!access(name, 3) || !access(name, 4)) {  // Проверим доступность файла

            if ((file = fopen(name, "r")) != nullptr) {
                fseek(file, 0, SEEK_END);
                *file_size = ftell(file);
                fseek(file, 0, SEEK_SET);
            } else {
                printf("\n""ERROR open_file UNIX: %s nullptr \n", name);
            }

        } else {
            printf("\n""ERROR open_file UNIX: "
                   "the file %s is ", name);
            if (access(name, 0))
                printf("not present\n");
            else
                printf("access is denied\n");
        }

    } else {

        if ((file = fopen(name, "rb")) != nullptr) {
            struct stat file_specification{};
            if (!fstat(fileno(file), &file_specification)) {
                *file_size = file_specification.st_size;
            } else {
                printf("\n""ERROR open_file: %s nullptr \n", name);
            }
        } else {
            printf("\n""ERROR open_file: "
                   "the file %s is either not present or access is denied\n", name);
            perror("meow");
        }
    }
    return file;
}


char *Read_File_To_Buffer(const char *name, int *state_func, bool UNIX) {
    const unsigned amount_of_free_RAM = 300; //MB

    assert (name != nullptr);
    assert (state_func != nullptr);

    // Сам очистит буффер при ошибке
    // В конце ставит \n \0 для удобства конвертирования
    // state_func == 0 ошибки отсутствуют
    // state_func == 1 файл пустой
    // state_func == 2 ошибка чтения или записи в файл
    // state_func == 3 не хватает оперативной памяти для считывания текста

    unsigned long file_size = 0;
    bool error_read = false;
    FILE *file = open_file(name, &file_size, UNIX);

    if (file_size == 0) {
        *state_func = 1;
        if (file) fclose(file);
        return nullptr;
    }
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /* Проверка на наличие RAM для buf
    struct sysinfo info = {}; // The toopenkiy CLion cannot handle it :((
    sysinfo(&info);
    if (info.freeram / (1024 * 1024) - file_size < amount_of_free_RAM) {
        printf("Read_File_To_Buffer: ERROR Not enough RAM for reading text");
        fclose(file);
        *state_func = 3;
        return nullptr;
    }
     //*/
    
    
    
    // В buf будет храниться весь файл name + знак '\0'
    char *buf = (char *) calloc(file_size + 1, sizeof(char));
    if (fread(buf, sizeof(char), file_size, file) != file_size) {
        if (feof(file)) {
            printf("Read_File_To_Buffer: Error fread file %s\n"
                   "feof(%s) == 1\n", name, name);
            error_read = true;
        } else if (ferror((file))) {
            printf("Read_File_To_Buffer: Error fread file %s\n"
                   "ferror(%s) == 1\n", name, name);
            error_read = true;
        }
    }

    fclose(file);

    if (error_read) {
        *state_func = 2;
        free(buf);
        return nullptr;
    }

    buf[file_size - 1] = '\n';
    buf[file_size] = '\0';
    *state_func = 0;
    return buf;
}


template <typename data_t>
Matrix<data_t>::Matrix ():
size_(1)
{
    data_ = new subMatrix<data_t>* [size_];
    ASSERT_MAT(data_ != NULL)
    for (int i = 0; i < size_; i++) {
        data_ [i] = new subMatrix<data_t> (size_);
        
        ASSERT_MAT(data_[i] != NULL)
    }
    
}


template <typename data_t>
Matrix<data_t>::Matrix (int size):
size_(size)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new subMatrix<data_t>* [size_];
    ASSERT_MAT(data_ != NULL)
    for (int i = 0; i < size_; i++) {
        data_ [i] = new subMatrix<data_t> (size_);
        ASSERT_MAT(data_ != NULL)
    }
    
}


template <typename data_t>
Matrix<data_t>::Matrix (Matrix<data_t>& M):
size_(M.size_)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new subMatrix<data_t>* [size_];
    ASSERT_MAT(data_ != NULL)
    for (int i = 0; i < size_; i++) {
        data_ [i] = new subMatrix<data_t> (size_);
        ASSERT_MAT(data_ != NULL)
    }
    
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            (*this) [i] [j] = M[i][j];
        }
    }
}


template <typename data_t>
Matrix<data_t>::~Matrix () {
    delete [] data_;
}

/*
 2
 -1  -10
 -10  -1
 
 
 */
template <typename data_t>
int Matrix<data_t>::BufToMatrix (char* buf) {
    
    for (int i = 0, k = 1, h = 1, s = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++, h = 1, s = 0) {
            for (; (buf [k] == ' ') || ((buf [k] == '\n')); k++);
            ASSERT_MAT(buf[k] != '\0')
            if (buf [k] == '-') {
                k++;
                h = -1;
            }
            ASSERT_MAT(buf[k] != '\0')
            for (; (buf [k] != ' ') && (buf [k] != '\n') && (buf [k] != '\0'); k++) {
                s = s * 10 + (buf [k] - '0');
            }
            (*this) [i] [j] = h * s;
            
        }
    }
    return 0;
}


template <typename data_t>
int Matrix<data_t>::SubMatrixDet(int ni, int nj, Matrix<data_t> &M, int size) {
    
    
    if (size == -1) {
        size = size_;
    }
    
    ASSERT_MAT(size > 0)
    
    for (int i = 0, g = 0; i < size - 1; i++, g++) {
        if (g == nj)
            g++;
        for (int j = 0, h = 0; j < size - 1; j++, h++) {
            
            if (h == ni)
                h++;
            M [i] [j] = ((*this) [g] [h]);
        }
    }
    return 0;
}


template <typename data_t>
data_t Matrix<data_t>::det (int size) {
    
    if (size == -1) {
        size = size_;
    }
    
    ASSERT_MAT(size > 0)
    
    if (size == 1)
        return ((*this) [0] [0]);
    
    data_t D = 0;
    Matrix<data_t>* M;
    M = new Matrix<data_t> (size - 1);
    ASSERT_MAT(data_ != NULL)
    
    
    for (int i = 0, j = 1; i < size; i++, j *= -1) {
        if ((*this) [0] [i] != 0) {
            SubMatrixDet(i,0,  *M, size);
            D += ((*this) [0] [i]) * M->det() * j;
        }
    }
    
    
    delete M;
    
    return D;
}

//*
template <typename data_t>
bool Matrix<data_t>::nondegeneracy() {
    
    if (this->det() == 0) {
        return false;
    }
    
    Matrix<data_t>* M;
    M = new Matrix<data_t> (size_ - 1);
    ASSERT_MAT(data_ != NULL)
    
    
    for (int i = 0; i < size_; i++) {
        SubMatrixDet(i,i,  *M);
        if (M->det() == 0) {
            delete M;
            return false;
        }
    }

    delete M;
    
    return true;
}

template <typename data_t>
bool Matrix<data_t>::positive() {
    
    if (this->det() <= 0) {
        return false;
    }
    
    if (size_ == 1) {
        return true;
    }
    
    Matrix<data_t>* M;
    M = new Matrix<data_t> (size_ - 1);
    ASSERT_MAT(data_ != NULL)
    
    SubMatrixDet(size_ - 1, size_ - 1,  *M);
    
    if (!(M->positive())) {
        delete M;
        return false;
    }

    delete M;
    
    return true;
}


template <typename data_t>
bool Matrix<data_t>::symmetry() {
    
    for (int i = 0; i < size_ - 1; i++) {
        for (int j = i + 1; j < size_; j++) {
            if ((*this) [i] [j] != (*this) [j] [i])
                return false;
        }
    }
    
    return true;
}

//*/

template <typename data_t>
subMatrix<data_t>& Matrix<data_t>::operator [] (int i) {
    
    ASSERT_MAT((i>=0 && i<size_))
    
    return *(data_[i]);
}

template <typename data_t>
data_t& subMatrix<data_t>::operator [] (int i) {
    ASSERT_MAT((i>=0 && i<size_))
    return data_[i];
}


template <typename data_t>
std::ostream& operator<< (std::ostream &out, Matrix<data_t> &M)
{
    for (int i = 0; i < M.size_; i++) {
        out << "| ";
        for (int j = 0; j < M.size_; j++) {
            out << M [i] [j];
            out << " ";
        }
        out << "|\n";
    }
    
    
    return out;
}
        
template <typename data_t>
std::istream& operator>> (std::istream &in, Matrix<data_t> &M)
{
    
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            in >> M [i] [j];
        }
    }
    
    return in;
}


template <typename data_t>
Matrix<data_t>& Matrix<data_t>::operator = (const Matrix<data_t> & A) {
        
    ASSERT_MAT(A.size_ == (*this).size_)
        
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
        (*this) [i] [j] = A.data_[i]->operator[](j);
        //A.data_[i].operator[](j);
        }
    }
    
    return *this;
}

template <typename data_t>
Matrix<data_t>& Matrix<data_t>::operator = (data_t x) {
    
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
        (*this) [i] [j] = x;
        //A.data_[i].operator[](j);
        }
    }
    
    return *this;
}

        
template <typename data_t>
bool operator == (Matrix<data_t>& A, Matrix<data_t>& B) {
    ASSERT_MAT(A.size_==B.size_)
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
            if (B [i] [j] != (A [i] [j]))
                return false;
        }
    }
    return true;
}


template <typename data_t>
bool Matrix<data_t>::operator != (const Matrix<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    if ((*this) == A) {
        return false;
    }
    return true;
}

template <typename data_t>
bool Matrix<data_t>::operator == (const Matrix<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
            if ((*this) [i] [j] != A.data_[i]->operator[](j))
                return false;
        }
    }
    return true;
}
            


                
                

template <typename data_t>
Matrix<data_t> Matrix<data_t>::T () {
    Matrix<data_t> M (size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = (*this) [j] [i];
        }
    }
    return M;
}






template <typename data_t>
double Vector<data_t>::abc () {
    data_t sum = 0;
    for (int i = 0; i < size_; i++) {
        sum += data_ [i] * data_ [i];
    }
    return sqrt(sum);
}


template <typename data_t>
Vector<data_t>::Vector ():
size_(1)
{

    data_ = new data_t [size_] {};
    ASSERT_MAT(data_ != NULL)
}


template <typename data_t>
Vector<data_t>::Vector (int size):
size_(size)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new data_t [size_] {};
    ASSERT_MAT(data_ != NULL)
    
}


template <typename data_t>
Vector<data_t>::Vector (Vector<data_t>& V):
size_(V.size_)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new data_t [size_] {};
    ASSERT_MAT(data_ != NULL)
    
    for (int i = 0; i < size_; i++) {
        (*this) [i] = V [i];
    }
}


template <typename data_t>
Vector<data_t>::~Vector () {
    delete [] data_;
}


template <typename data_t>
data_t& Vector<data_t>::operator [] (int i) {
    
    ASSERT_MAT((i>=0 && i<size_))
    
    return data_[i];
}


template <typename data_t>
std::ostream& operator<< (std::ostream &out, Vector<data_t> &V)
{
    out << "(";
    for (int i = 0; i < V.size_; i++) {
        out << V [i];
        if(i < V.size_ - 1)
            out << " ";
    }
    out << ")";
    return out;
}
        
template <typename data_t>
std::istream& operator>> (std::istream &in, Vector<data_t> &V)
{
    for (int i = 0; i < V.size_; i++) {
        in >> V [i];
    }
    return in;
}


template <typename data_t>
Vector<data_t>& Vector<data_t>::operator = (const Vector<data_t> & A) {
        
    ASSERT_MAT(A.size_ == (*this).size_)
        
    for (int i = 0; i < A.size_; i++) {
        (*this) [i] = A.data_[i];
    }
    
    return *this;
}

template <typename data_t>
Vector<data_t>& Vector<data_t>::operator = (data_t x) {
        
    for (int i = 0; i < size_; i++) {
        (*this) [i] = x;
    }
    
    return *this;
}

template <typename data_t>
Vector<data_t> operator - (Vector<data_t>& A, Vector<data_t>& B)  {
    
    Vector<data_t> M(A.size_);
    for (int i = 0; i < M.size_; i++) {
            M [i] = A [i] - B [i];
    }
    return M;
}




template <typename data_t>
Vector<data_t> operator * (Matrix<data_t>& A, Vector<data_t>& B) {
    ASSERT_MAT(A.size_ == B.size_)
    Vector<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] += A [i] [j] * B [j];
        }
    }
    return M;
}
#undef ASSERT_MAT
