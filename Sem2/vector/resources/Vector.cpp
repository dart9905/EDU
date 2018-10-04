/*!
 \file
 \authors MARK99
 \version A1.7mac
 \date 2:27 18.04.2018
 \bug ¯\_(ツ)_/¯
 \brief class vectormy
 This class is designed to study cpp.
 PS I really want to sleep, but I need to write the documentation...
 */
#define ASSERT_VECTOR( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFilesVectormy.txt", "at");\
\
fprintf(files, "==========ASSERT_VECTOR=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}
//
//
//      Define to dump data
//
//
#define DUMP_(str) //Dump(str);



/*!
 \brief A special class for outputting errors in a myvector.
 
  Used to output errors and exceptions in a myvector through try-catch.
 */
class ERROR_myvector_t {
public:
    ERROR_myvector_t (char* str = "ERROR in myvector", char* f = __FILE__, int n = __LINE__):
    data(str),
    file(f),
    num(n) {}
    
    /*!
     Method for displaying warnings.
    */
    int what () const {
        printf("warning (myvector): %s, in file %s, in line %i.", data, file, num);
        return 0;
    }
    
    /*!
     Method for outputting an error and terminating the program with an assert.
    */
    int end () const {
        printf("ERROR (myvector): %s, in file %s, in line %i.\n", data, file, num);
        ASSERT_VECTOR(0);
        return 0;
    }
    
    ///String to store the error.
    char* data;
    ///The string for storing the file's name.
    char* file;
    ///Line for storing the line number.
    int num;
};



/*!
 \brief Class vectormy
 
 Everything is still good, even there is an override operator [] for double.
 */
template <typename data_T>
class vectormy {
public:
    // constructors and disruptors
    /*!
     Default constructor for class.
     \param[in] arg - specified to determine the size of the array, the default is 10
    */
    explicit vectormy (int arg = 10);
    
    /*!
     Initializer is a data sheet. For example, for int: {2,1,5,6, ...}.
     \param[in] list
    */
    vectormy (const std::initializer_list<data_T>& init);
    
    /*!
     Copy constructor.
     \param[in] that
     */
    vectormy (const vectormy<data_T>& that);
    
    /*!
     Short copying constructor.
    */
    vectormy (vectormy<data_T>&& that);
    
    
    /*!
     Disruptors
     */
    ~vectormy ();
    
    
    
    //operators
    /*!
     Overloaded operator = for vectormy.
     */
    vectormy&   operator = (vectormy & arg) {
        this->swap(arg);
        DUMP_("Vector assignment\n")
        return *this;
    }
    
    /*!
     Overloaded operator = for an array of the same type as the myvector itself.
     */
    vectormy&   operator = (data_T* arg) {
        for (int i = 0; i < size_; i++) {
            data_[i] = arg [i];
        }
        DUMP_("Vector assignment\n")
        return *this;
    }
    
    /*!
     Overloaded operator = for a shortlifed myvector.
     */
    vectormy& operator=(vectormy&& that)
    {
        Swap(that);
    }
    
    /*!
     Overloaded operator [] for int.
     */
    data_T& operator [] (int i);
    
    // const data_T& operator [] (int i) const;
    
    /*!
     Overloaded operator [] for myvector which extrapolates the given vector and gives them.
     */
    double operator [] (double d);
    
    
    
    //function
    /*!
     Dump the vector data. Blocked by the define, to increase the speed of the code.
    */
    bool    Dump (const char* str) const;
    /*
     template <typename data_T>
     bool vectormy <data_T> :: Dump (const char* str)
    */
    
    
    /*!
     Function to get the size of an array.
     */
    int     size () const;
    
    /*!
     Function for getting the user address on the data array.
     */
    data_T* direction () const {
        return data_;
    }
    
    
    //memory
    
private:
    /*!
     pointer to a data array.
    */
    data_T* data_ = nullptr;
    
    /*!
     The size of the array.
    */
    int     size_ = 0;
    
    /*!
     Redefined swap.
    */
    void    swap (vectormy& arg);
    
    /*!
     File name for log output.
    */
    char* _LOG_FILES_NAME = "LogFilesVectormy.txt";
    int     capasity_ = 0;
};



template <typename data_T>
vectormy <data_T> :: vectormy (int arg):
size_(arg),
capasity_(0),
data_(nullptr) {
    data_ = new data_T [size_] {NULL};
    ASSERT_VECTOR(data_)
    DUMP_("Craft new vector\n")
}


template <typename data_T>
vectormy <data_T> ::  vectormy (const std::initializer_list<data_T>& init) :
data_ (new data_T [init.size()]),
size_ (init.size()),
capasity_(0) {
    std::copy (init.begin(), init.end(), data_);
}



template<typename data_T>
vectormy <data_T> ::  vectormy (const vectormy<data_T>& that):
capasity_ (that.capasity_),
size_ (that.size_),
data_ (new data_T [size_])
{
    for(int i = 0; i < size_; i++)
        data_ [i] = that.data_ [i];
}



template<typename data_T>
vectormy <data_T> ::  vectormy (vectormy<data_T>&& that):
capasity_   (that.capasity_),
size_ (that.size_),
data_ (that.data_)
{
    if(&that != this)
    {
        that.capacity_ = 0;
        that.size_ = 0;
        that.data_ = nullptr;
    }
}



template <typename data_T>
vectormy <data_T> :: ~vectormy () {
    if (data_ != nullptr)
        delete [] data_;
    DUMP_("Delete vector\n")
};



template <typename data_T>
int vectormy <data_T> :: size () const {
    return size_;
}



template <typename data_T>
void vectormy <data_T> :: swap (vectormy& arg) {
    std::swap(size_, arg.size_);
    std::swap(capasity_, arg.capasity_);
    std::swap(data_, arg.data_);
}



template <typename data_T>
data_T&  vectormy <data_T> :: operator [] (int i) {
    ASSERT_VECTOR(i >= 0)
    if ((i >= 0) && (i < size_))
        return (data_[i]);
    else {
        int new_size = 0;
        if (i >= size_ * 2)
            new_size = i * 2;
        else
            new_size = size_ * 2;
        
        vectormy copy (new_size);
        
        for (int j = 0; j < size_; j++)
            copy.data_ [j] = data_[j];
        
       *this= copy;
       return (data_[i]);
    }
    
}



template <typename data_T>
std::ostream& operator << (std::ostream& stream, const vectormy <data_T>& vector) {
    stream << "{ ";
    std::copy (vector.direction(), vector.direction() + vector.size(), std::ostream_iterator <data_T> (stream, " "));
    stream << "}";
    
    return stream;
}


/*!
 Search for the angle of inclination to the graph at a point at given points.
 
 \param[in] dx - step
 \param[in] xb - left point
 \param[in] yb - left point
 \param[in] xa - tangent
 \param[in] ya - tangent
 \param[in] xc - right point
 \param[in] yc - right point
 \return angle of inclination of the tangent to the graph.
*/
double tiltangle (double dx , double xb, double yb, double xa, double ya, double xc, double yc) {
    if ((dx < 0) || (xb < 0) || (xa < 0) || (xc < 0))
        throw ERROR_myvector_t("array indexes can not be negative");
    
    if (yc == yb)
        return 0;
    return (sqrt(((ya - yb) * (ya - yb) + dx * dx) * ((ya - yc) * (ya - yc) + dx * dx)) - dx * dx - (ya - yb) * (ya - yc)) / (dx * (yc - yb));
}



double dx_ (double dx, double k) {
    if (dx < 0)
        throw ERROR_myvector_t("interval step can not be negative");
    return dx / 2 * sqrt(1 / (1 + k * k));
}



double coord_y (double dt, double y1, double y2) {
    return y1 + (y2 - y1) * dt;
}


/*!
 Approximation by the Bezier polynomial.
 \param[in] dt - step
 \param[in] y_min_1 - left point of the curve
 \param[in] y_min_c - left helped point
 \param[in] y_max_c - right helped point
 \param[in] y_max_1 - right point of the curve
 \return the coordinate of the point
 
*/
double finalcoord_y (double dt, double y_min_1, double y_min_c, double y_max_c, double y_max_1) {
    return coord_y(dt, coord_y(dt, coord_y(dt, y_min_1, y_min_c), coord_y(dt, y_min_c, y_max_c)), coord_y(dt, coord_y(dt, y_min_c, y_max_c), coord_y(dt, y_max_c, y_max_1)));
}



template <typename data_T>
double  vectormy <data_T> :: operator [] (double d) {
    
    
    if (d < 0)
        return 0.0;
    
    int ind_max = ceil(d);
    int ind_min = floor(d);
    
    
    double dx = 1;
    /*!
     Coordinates of points tangent to the graph at the right point: with 1 lying left, 2 right.
     The point for the tangent is taken with respect to the index-point of the array.
     */
    double x_max_1 = 0;
    double y_max_1 = 0;
    double x_max_2 = 0;
    double y_max_2 = 0;
    
    /*!
     Coordinates of points tangent to the graph at the left point: 1 being left, 2 right.
     The point for the tangent is taken with respect to the index-point of the array.
     */
    double x_min_1 = 0;
    double y_min_1 = 0;
    double x_min_2 = 0;
    double y_min_2 = 0;
    
    if (ind_max <= size_) {
        x_max_1 = ind_max;
        y_max_1 = data_[ind_max];
        if (ind_max + 1 < size_) {
            x_max_2 = ind_max + 1;
            y_max_2 = data_[ind_max + 1];
        } else {
            x_max_2 = ind_max;
            y_max_2 = data_[ind_max];
        }
    } else
        return 0.0;
    if (ind_min <= size_) {
        x_min_1 = ind_min;
        y_min_1 = data_[ind_min];
        if (ind_min - 1 >= 0) {
            x_min_2 = ind_min - 1;
            y_min_2 = data_[ind_min - 1];
        } else {
            x_min_2 = ind_min;
            y_min_2 = data_[ind_min];
        }
    } else
        return 0.0;
    
    
    /*!
     x_min_2 < x_min_1 < x_max_1 < x_max_2
     the search for a tangent to the graph at point x_min_1: k_min and x_max_1: k_max
     */
    double k_min = 0.0;
    double k_max = 0.0;
    try {
        k_min = tiltangle(dx, x_min_2, y_min_2, x_min_1, y_min_1, x_max_1, y_max_1);
        k_max = tiltangle(dx, x_min_1, y_min_1, x_max_1, y_max_1, x_max_2, y_max_2);
    } catch (const ERROR_myvector_t& e) {
        e.end();
    }
    
    /*!
     Finding a reference point for a polynomial
     right control point: y_max_c
     left control point: y_min_c
     */
    double y_max_c = 0.0;
    double y_min_c = 0.0;
    
    try {
        y_max_c = y_max_1 - k_max * dx_ (dx, k_max);
        y_min_c = y_min_1 + k_min * dx_ (dx, k_min);
    } catch (const ERROR_myvector_t& e) {
        e.end();
    }
    
    double dt = d - ind_min;
    
    /*!
     approximation by the Bezier polynomial
     x_min_1 < search x < x_max_1
     */
    return finalcoord_y(dt, y_min_1, y_min_c, y_max_c, y_max_1);
}




template <typename data_T>
bool vectormy <data_T> :: Dump (const char* str) const {
    FILE *files = fopen (_LOG_FILES_NAME, "at");
    ASSERT_VECTOR(files);
    
    fprintf(files, "==========vectormy==========\n\n");
    fprintf(files, "%s\n", str);
    fprintf(files, "Size = %i\n", size_);
    fprintf(files, "Capasity = %i\n", capasity_);
    for (int i = 0; i < size_; i++)
        fprintf(files, "array [%i] = %i\n", i, data_[i]);
    fprintf(files, "\n===========================\n\n");
    
    fclose(files);
    return 0;
}


//
//
//BOO..tay
//
//
/*!
 \brief Class vectormy for bool
 
 For economical use of memory. For bool it is used by bit.
 */
template <>
class vectormy <bool>
{
public:
    /*!
     \brief Helper class for myvector.
     
     For economical use of memory. For bool it is used by bit.
     */
    class RetBool
    {
    public:
        /// Number of the pack with the bit to be changed
        char* chang_num_  = 0;
        /// Offset in the pack
        size_t offset_   = 0;
        /// "Checker"
        bool ready_ = false;
        
        /*!
         Default constructor
        */
        RetBool() {};
        
        /*!
         Operator bool
        */
        operator bool()
        {
            if(!chang_num_)      return false;
            
            unsigned char bit = 1;
            bit <<= offset_;
            bit &= (*chang_num_);
            bit >>= offset_;
            return (bit == 1) ? true : false;
        }
        
        /// Operator =
        RetBool& operator = (const bool& new_elem)
        {
            unsigned char bit = new_elem ? 1 : 0;
            bit <<= offset_;
            unsigned char cleaner = ~(1 << offset_);
            (*chang_num_) &= cleaner;
            (*chang_num_) |= bit;
            
            return *this;
        }
        
        /// Setter
        void Set(char* chang_num, size_t offset)
        {
            chang_num_ = chang_num;
            offset_   = offset;
        }
    };
    
    /*!
     Default constructor for class.
     \param[in] parameters_expected - specified to determine the size of the array, the default is 10
    */
    vectormy (size_t parameters_expected = 10);
    
    /*!
     Copy constructor.
     \param[in] that
    */
    vectormy (const vectormy<bool>& that);
    
    /*!
     Short copying constructor.
     */
    vectormy (vectormy<bool>&& that):
    data_ (that.data_),
    capasity_ (that.capasity_),
    size_ (that.size_)
    {
        if(&that != this)
        {
            that.data_ = nullptr;
        }
    }
    
    /*!
     Default constructor
    */
    ~vectormy ();
    
    
    
    // Operators
    /*!
     Overloaded operator [] for int.
    */
    RetBool& operator [] (size_t index);
    
    /*!
     Overloaded operator = for a shortlifed myvector.
    */
    vectormy <bool> & operator = (vectormy <bool> && that)
    {
        Swap (that);
        
        return *this;
    }
    
    /*!
     Overloaded operator = for vectormy.
    */
    vectormy <bool> & operator = (const vectormy <bool> & that)
    {
        vectormy <bool> tmp_object(that);
        Swap(tmp_object);
        
        return *this;
    }
    
    
    
    /// "push" operator
    bool operator<<(const bool& new_elem);
    
    /// "pop"  operator
    bool operator>>(bool& new_elem);
    
    
    
    //memory
    RetBool bit_container_;
    bool    garbage_collector_  = 0;
    
    
    
    //function
    /*!
     Redefined swap.
     */
    int Swap    (vectormy <bool> & that);
    bool Resize (size_t new_size);
private:
    
    /*!
     pointer to a data array.
     */
    char*   data_               = nullptr;
    size_t  capasity_           = 0;
    
    /*!
     The size of the array.
     */
    size_t  size_               = 0;
};



vectormy <bool> :: vectormy (size_t parameters_expected):
capasity_    (parameters_expected/8 + 1),
size_        (parameters_expected),
data_        (new char [capasity_])
{}


vectormy <bool> :: vectormy (const vectormy <bool> & that):
capasity_    (that.capasity_),
size_ (that.size_)
{
    data_ = new char [capasity_];
    
    for(size_t i = 0; i < capasity_; i++)
        data_ [i] = that.data_ [i];
}


vectormy <bool> :: ~vectormy()
{
    delete [] data_;
}



vectormy <bool> :: RetBool& vectormy <bool> :: operator [] (size_t i)
{
    
    size_t pack_num = i / 8;
    size_t offset   = i - pack_num * 8;
    
    bit_container_.Set(data_ + pack_num, offset);
    return bit_container_;
}





bool vectormy <bool> :: operator << (const bool& new_elem)
{
    if(size_ <= 0)
        Resize(1);
    else
        return false;
    
    if(size_ >= capasity_ * 8)
        Resize(capasity_ + 1);
    else
        return false;
    
    size_t pack_num = size_/8;
    size_t offset   = size_ - pack_num*8;
    
    unsigned char tmp = new_elem ? 1 : 0;
    tmp <<= offset;
    
    data_ [pack_num] |= tmp;
    size_++;
    
    return true;
}

bool vectormy <bool> :: operator >> (bool& new_elem)
{
    if(size_ <= 0)
        return false;
    
    unsigned char bit = 1;
    unsigned char cleaner = 0;
    
    size_t offset = size_ - (capasity_ - 1)*8 - 1;
    
    bit <<= offset;
    cleaner = ~bit;                                 // bit = 00010000, cleaner = 11101111
    bit &=  data_ [capasity_ - 1];
    data_ [capasity_ - 1] &= cleaner;
    bit >>= offset;
    
    new_elem = (bit == 1) ? true : false;
    
    data_--;
    
    if(size_ < capasity_/2)
        Resize(capasity_/2);
    else
        return false;
    
    return true;
}


// =====================================================================================
//

bool vectormy <bool> :: Resize (size_t new_size)
{
    size_t min_size = (capasity_ <  new_size) ? capasity_ : new_size;
    
    char* new_arr = nullptr;
    
    new_arr = new char [new_size];
    
    for(size_t i = 0; i < min_size; i++)
        new_arr [i] = data_ [i];
    
    delete data_;
    data_ = new_arr;
    capasity_ = new_size;
    
    return true;
}




#undef DUMP_()
#undef ASSERT_STACK
