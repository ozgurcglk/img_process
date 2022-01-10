/**********************************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip 
 and it is modified for ELM463/667
 
 * Image.cpp - the image library which implements
 *             the member functions defined in Image.h
 *
 * Author: Hairong Qi, ECE, University of Tennessee
 *
 * Created: 02/05/02
 *
 * Copyright (C) hqi@utk.edu
 **********************************************************/

#include "Image.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

/**
 * Default constructor.
 */ 
Image::Image() {
  image = NULL;
  nrows = 0;
  ncols = 0;
  maximum = 255;
  //createImage(0, 0);
}

/**
 * Constructor for grayscale images.
 * @param nrows Numbers of rows (height).
 * @param ncols Number of columns (width).
 * @return The created image.
 */
Image::Image(int nRows, int nCols) {
  if (nRows<=0 || nCols<=0) {
    cout << "Image: Index out of range.\n";
    exit(3);
  }
  image = NULL;
  createImage(nRows, nCols);
}

/**
 * Copy constructor. 
 * @param img Copy image.
 * @return The created image.
 */
Image::Image(const Image &img) {
  int rows, cols;

  image = NULL;
  nrows = img.getRow();
  ncols = img.getCol();
  createImage(nrows, ncols);             // allocate memory
  
  for (rows=0; rows < nrows; rows++)
    for (cols=0; cols < ncols; cols++)
		image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Destructor.  Frees memory.
 */
Image::~Image() {
  if (image)
    delete [] image;       // free the image buffer
}






/**
 * Allocate memory for the image and initialize the content to be 0.
 */
void Image::createImage() {

  if (image != NULL)
    delete [] image;

  maximum = 255;

  image = (float *) new float [nrows * ncols];
  if (!image) {
    cout << "CREATEIMAGE: Out of memory.\n";
    exit(1);
  }

  initImage();
}


/**
 * Allocate memory for the image and initialize the content to be zero.
 * @param r Numbers of rows (height).
 * @param c Number of columns (width).
 */
void Image::createImage(int numberOfRows, int numberOfColumns) {
  
  if (image != NULL)
    delete [] image;

  nrows = numberOfRows;
  ncols = numberOfColumns;
  maximum = 255;

  image = (float *) new float [nrows * ncols];
  if (!image) {
    cout << "CREATEIMAGE: Out of memory.\n";
    exit(1);
  }

  initImage();
}

/**
 * Initialize the image.
 * @para init The value the image is initialized to. Default is 0.0.
 */
void Image::initImage(float initialValue) {
  int i;

  for (i = 0; i < nrows * ncols; i++)
    image[i] = initialValue;
}

/**
 * Returns the total number of rows in the image.
 * @return Total number of rows.
 * \ingroup getset
 */
int Image::getRow() const {
  return nrows;
}

/**
 * Returns the total number of columns in the image.
 * @return Total number of columns.
 * \ingroup getset
 */
int Image::getCol() const {
  return ncols;
}

/**
 * Returns the maximum pixel value of a gray-level image. 
 * @return The intensity of that pixel.
 * \ingroup getset
 */
float Image::getMaximum() const {
  int i, j;
  float maxi=-10000;

 
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      if (maxi < image[i*ncols+j])
	maxi = image[i*ncols+j];
  
  return maxi;
}


/**
 * Returns the minimum pixel value of the image.
 * @return The minimum pixel value.
 * \ingroup getset
 */
float Image::getMinimum() const {
  int i, j;
  float mini=10000; 

  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      if (mini > image[i*ncols+j])
	mini = image[i*ncols+j];

  return mini;
}



/**
 * Returns the pixel value at rows, cols
 * @return The pixel value
 * \ingroup getset
 */
float Image::getPix(int rows, int cols) {
  return image[rows * ncols + cols];
}


/**
 * Returns the image. 
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::getImage() const {
  Image temp;
  int rows, cols;
  
  temp.createImage(nrows, ncols);   // temp is a gray-scale image
  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      temp(rows, cols) = image[rows * ncols + cols];
      
  return temp;
}

/**
 * Sets the total number of rows in an image.
 * @param r Total number of rows.
 * \ingroup getset
 */
void Image::setRow(int numberOfRows) {
  nrows = numberOfRows;
}

/**
 * Sets the total number of columns in an image.
 * @param c Total number of columns.
 * \ingroup getset
 */
void Image::setCol(int numberOfColumns) {
  ncols = numberOfColumns;
}


/**
 * Sets the pixel value at rows,cols.
 * @param row and col index.
 * \ingroup getset
 */
void Image::setPix(int rows, int cols, float value) {
  image[rows * ncols + cols] = value;
}


/**
 * Sets the image given a grayscale image. 
 * \ingroup getset
 */
void Image::setImage(Image &img) {
  int rows, cols;

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Overloading () operator
 * \ingroup overload
 * @param i Row
 * @param j Column
 */
float & Image::operator()(int rows, int cols) const {
  return image[rows * ncols + cols];
}

/**
 * Overloading = operator.
 * \ingroup overload
 * @param img Image to copy.
 * @return Newly copied image.
 */
const Image Image::operator=(const Image& img) {
  int rows, cols;

  if (this == &img)
    return *this;

  nrows = img.getRow();
  ncols = img.getCol();
  createImage(nrows, ncols);             

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
	(*this)(rows, cols) = img(rows, cols);

  return *this;
}

/**
 * Overloading + operator.
 * \ingroup overload
 * @param img Image to add to specified image.
 * @return Addition of the two images.
 */
Image Image::operator+(const Image& img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator+: "
         << "Images are not of the same size or type, can't do addition\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] + img(i,j);

  return temp;
}

/**
 * Overloading - operator.
 * \ingroup overload
 * @param img Image to subtract from specified image.
 * @return Subtraction of the two images.
 */
Image Image::operator-(const Image &img) const {
   int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator-: "
         << "Images are not of the same size or type, can't do subtraction\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] - img(i,j);

  return temp;
}

/**
 * Overloading * operator.  This function does pixel by pixel multiplication.
 * \ingroup overload
 * @param img Image to multiply with specified image.
 * @return Multiplication of the two images.
 */
Image Image::operator*(const Image &img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator*: "
         << "Images are not of the same size or type, can't do multiplication\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] * img(i,j);

  return temp;
}

/**
 * Overloading / operator.  This function does pixel by pixel division.
 * Specified image is the dividend.
 * \ingroup overload
 * @param img Image to be divided (divisor).
 * @return Quotient of the two images.
 */
Image Image::operator/(const Image &img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator/: "
         << "Images are not of the same size or type, can't do division\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] / ( img(i,j) + 0.001 );

  return temp;
}


/**
 * Overloading << operator.  Output the image to the specified destination.
 * \ingroup overload
 * @param out The specified output stream (or output destination).
 * @param img Image to be output.
 * @result Output image to the specified file destination.
 */
ostream & operator<<(ostream &out, Image &img) {
  int rows, cols;
  

    for (rows = 0; rows < img.getRow(); rows++) {
      for (cols = 0; cols < img.getCol(); cols++)
        out << setw(4) << img(rows, cols) << ' ';
      out << endl;
    }

  return out; 
}

/**
 * Overloading / operator.  The left operand is the image and the right
 * is the dividend (a double point number). Each pixel in the image is 
 * divided by the double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param val A double point number as the right operand.
 * @result Image divided by a double point number.
 */
Image operator/(Image &img, double val) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) / val;
  
  return temp;
}

/**
 * Overloading * operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is multiplied by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image multiplied by a double point scalar.
 */
Image operator*(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) * s;
  
  return temp;
}


/**
 * Overloading + operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is added by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image add a double point scalar.
 */
Image operator+(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) + s;
  
  return temp;
}  
  
/**
 * Overloading - operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is subtracted by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image subtract a double point scalar.
 */
Image operator-(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) - s;
  
  return temp;
} 

/**
 * Read image from a file                     
 * @param fname The name of the file 
 * @return An Image object
 */
  void Image::readImage(char *fname) {
  ifstream ifp;
  char dummy[80];
  unsigned char *img;
  int rows, cols;
  int nRows, nCols, nt, maxi;

  ifp.open(fname, ios::in | ios::binary);

  if (!ifp) {
    cout << "readImage: Can't read image: " << fname << endl;
    exit(1);
  }

  // identify image format
  ifp.getline(dummy, 80, '\n');

  if (dummy[0] == 'P' && dummy[1] == '5') 
     ;
  else {
    cout << "readImage: Can't identify image format." << endl;
    exit(1);
  }

  // skip the comments
  ifp.getline(dummy, 80, '\n');

  while (dummy[0] == '#') {
    ifp.getline(dummy, 80, '\n');
  }

  // read the row number and column number
  sscanf(dummy, "%d %d", &nCols, &nRows);

  // read the maximum pixel value
  ifp.getline(dummy, 80, '\n');
  sscanf(dummy, "%d", &maxi); 
  if (maxi > 255) {
    cout << "Don't know what to do: maximum value is over 255.\n";
    exit(1);
  }

  if (image != NULL)
  delete [] image;
  
  nrows = nRows;
  ncols = nCols;
  maximum = 255;
  
  // read the image data
  img = (unsigned char *) new unsigned char [nRows * nCols];
  if (!img) {
    cout << "READIMAGE: Out of memory.\n";
    exit(1);
  }
  image = (float *) new float [nRows * nCols];
  if (!image) {
    cout << "READIMAGE: Out of memory.\n";
    exit(1);
  }

    ifp.read((char *)img, (nRows * nCols * sizeof(unsigned char)));
    
    for (rows = 0; rows < nRows; rows++)
      for (cols = 0; cols < nCols; cols++)
          image[rows * nCols + cols] = (float) img[rows * nCols + cols];
      
  ifp.close();
  
  delete [] img;
}


/**
 * Write image buffer to a file.
 * @param fname The output file name.
 */
void Image::writeImage(char *fname, bool flag) {
  ofstream ofp;
  int i, j;
  int nRows, nCols, nt;
  unsigned char *img;

  ofp.open(fname, ios::out | ios::binary);

  if (!ofp) {
    cout << "writeImage: Can't write image: " << fname << endl;
    exit(1);
  }


  ofp << "P5" << endl;
  ofp << ncols << " " << nrows << endl;

 
  ofp << 255 << endl;
  
  

  // convert the image data type back to unsigned char
  img = (unsigned char *) new unsigned char [nrows * ncols];
  if (!img) {
    cout << "WRITEIMAGE: Out of memory.\n";
    exit(1);
  }

  float maxi = getMaximum();
  float mini = getMinimum();
  
  
    for (i = 0; i< nrows; i++)
      for (j = 0; j < ncols; j++) {
	  // rescale if the flag is set
	  if ((maxi != mini) && flag == true)
	    img[i * ncols + j] = (unsigned char)  ((image[i * ncols + j]-mini)/(float)(maxi-mini)*255.0); 
	  // any intensity that is larger than the maximum would be set as maximum
	  else if (image[i * ncols + j] > 255)
	    img[i * ncols + j] = 255;
	  else if (image[i * ncols + j] < 0)
	    img[i * ncols + j] = 0;
	  else
	    img[i * ncols + j] = (unsigned char)  image[i * ncols + j]; 
      }
      
    ofp.write((char *)img, (nrows * ncols * sizeof(unsigned char)));


  ofp.close();
  delete [] img;
}




// YOUR FUNCTIONS

/**
 * Returns the image. 
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::thresholdImage(float thresholdValue, float lowValue, float highValue) {
  Image temp;
  int rows, cols;
  
  temp.createImage(nrows, ncols);   // temp is a gray-scale image
  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      if (image[rows * ncols + cols] <= thresholdValue) 
	temp(rows, cols) = lowValue;
      else
	temp(rows, cols) = highValue;
      
      
  return temp;
}

Image Image::customImg(){
  
  Image temp;
  int rows, cols;
  int r = 1; //piksel değeri

  temp.createImage(nrows, ncols);

  for (rows = 0; rows < nrows; rows++){
    for(cols = 0; cols < ncols; cols++){
     Image::setPix(rows, cols, r);
     temp(rows, cols) = r;
     r++ ;
    }
  }  


  return temp;
}

Image Image::negativeImg() {

  Image s; // görüntü tanımlandı.
  int r; // piksel değeri değişkeni.
  int L = 255; // maksimum piksel değeridir.
  int rows, cols; //satır ve sütunlar

  s.createImage(nrows, ncols); // görüntü oluşturuldu.

  for(rows = 0; rows < nrows; rows++){
    for(cols = 0; cols < ncols; cols++){
      // görüntünün piksel değerlerine negatif formül uygulanır.
      r = Image::getPix(rows, cols);
      s(rows, cols) = L - 1 - r;
    }
  }
  cout << "Negative formula has been applied.\n";
return s;

}


Image Image::logTransform(){

  Image s; //görüntü tanımlandı.
  int c = 1; //sabit.
  int r; //piksel değeri değişkeni.
  int L = 255; // maksimum piksel değeridir.
  int rows, cols; //satır ve sütunlar

  s.createImage(nrows, ncols);

  for(rows = 0; rows < nrows; rows++){
    for(cols = 0; cols < ncols; cols++){
      // görüntüye logaritmik dönüşüm uygulanır.
      r = Image::getPix(rows, cols);
      s(rows, cols) = ( (c*log(1+r)) * (L / log(1 + L)) ) ;

    }
  }
  cout << "Log transform has been applied.\n";

return s;

}


Image Image::gammaTransform(float gam){

  Image s; //görüntü tanımlandı.
  int c = 1; //sabit.
  int r; //piksel değeri değişkeni.
  int L = 255; // maksimum piksel değeridir.
  int rows, cols; //satır ve sütunlar

  s.createImage(nrows, ncols);

  for(rows = 0; rows < nrows; rows++){
    for(cols = 0; cols < ncols; cols++){
      //görüntüye gamma dönüşümü uygulanır.
      r = Image::getPix(rows, cols);
      s(rows, cols) = c*(pow(r,gam) * (L/pow(L, gam)));

    }
  }
  cout << "Gamma transform has been applied.\n";

return s;

}

Image Image::HistogramEqualization(){

  Image temp; // görüntü s yerine temp olarak oluştu ve bu şekilde s arrayi ile karışmadı
  int r; // piksel değeri
  int L = 256; // maks piksel
  int rows, cols; // satır ve sütunlar
  int res = nrows*ncols; // toplam boyut resolution olarak tanımlandı
  int inImage[res] {0}; // ilk görüntünün piksel değerlerini alacak olan array 
  // histogram equilization işlemleri sonucunda oluşacak tüm değerler için arrayler oluşturuldu
  float h[L] {0};
  float p[L] {0};
  float t[L] {0};
  float s[L] {0};
  int sum = 0;
  float sumPDF = 0;

  temp.createImage(nrows, ncols); // template görüntü oluşturuldu

  for(rows = 0; rows < nrows; rows++){ 
    for(cols = 0; cols < ncols; cols++){
      // görüntünün piksel değerleri array olarak alındı
        r = Image::getPix(rows, cols);
        inImage[rows * ncols + cols] = r;
    
    }
  } 

  for(rows = 0; rows < nrows; rows++){
    for(cols = 0; cols < ncols; cols++){
      for(int i = 0; i < L; i++){
      
      // Bu adımda i indeksi ile inImage arrayindeki değerler kontrol edildi ve aynı olan değerler sayıldı
        if( i == inImage[rows * ncols + cols] ){    
          h[i] += 1;
        }
       }  
    }
  } 

  // piksel tekrarlarının toplam 250000 tane olup olmadığı kontrol etmek icin cout yorumu kaldırılabilir.
  for(int i = 0; i < L; i++){
    sum += h[i];
  }
  //cout << " size " << total << endl;

  for(int i = 0; i < L; i++){
    // Burada PDF fonksiyonu değerleri bulunması için h arrayindeki pikseller çözünürlüğe bölündü     
      p[i] = h[i] / res; 

      sumPDF += p[i];
  }

// kontrol için PDF değerlerinin toplamının 1 olup olmadığı yazdırıldı
  cout << "PDF sum " << sumPDF << endl;

  for(int i = 0; i < L; i++){
    //Burada CDF fonksiyonundaki bir önceki değerlerin toplamı halinde ilerleyen değerler bulundu
    t[i] = p[i] + t[i - 1];

  }

// kontrol için CDF fonksiyonun son değerinin 1 olup olmadığı yazdırıldı
  cout << "last val of CDF " <<  t[L-1] << endl;

  for(int i = 0; i < L; i++){
    // Burada s arrayi t arrayinin değerlerini maksimum piksel ile çarpıp round ile yuvarlayarak elde edildi.
    s[i] = round( getMaximum() * t[i] );
  }

  for(rows = 0; rows < nrows; rows++){
    for(cols = 0; cols < ncols; cols++){
      /* Burada r değerine görüntünün pikselleri atandı ve daha sonra r değeri s arrayine indeks olarak verildi
      böylece temp öğesinde eskiden r pikselinin olduğu yerde artık o pikselin kaç tane bulunduğu değeri yani s[r] değeri yer almakta */
        r = Image::getPix(rows, cols);
        temp.setPix(rows, cols, s[r]);

    }
  }

return temp;

}

Image Image::DFT(){

  Image temp;
  int rows, cols;
  int L = 256;
  float r;
  const float PI = 3.141;

  temp.createImage(nrows, ncols); // temp görüntü oluşturuldu

  for(rows = 0; rows < nrows; rows++){ // satır için
    for(cols = 0; cols < ncols; cols++){ //sütun için
      
      r = Image::getPix(rows, cols); //satır ve sütundaki piksel değerleri alındı

      temp(rows, cols) += abs(r * (cos(2 * PI * (1.0 * rows * cols / nrows)) - sin(2 * PI * (1.0 * rows * cols / nrows))) ) ; // DFT formülü sin cos olarak uygulandı
      
    }
  }

  for(cols = 0; cols < ncols; cols++){ //sütun için
    for(rows = 0; rows < nrows; rows++){ //satır için
      
      r = Image::getPix(rows, cols); //satır ve sütundaki piksel değerleri alındı

      temp(rows, cols) += abs(r * (cos(2 * PI * (1.0 * rows * cols / ncols)) -  sin(2 * PI * (1.0 * rows * cols / ncols))) ) ; // DFT formülü sin cos olarak uygulandı
      
    }
  }

return temp; //görüntü döndürüldü

}

Image Image::IDFT(){

  Image temp;
  int rows, cols;
  int L = 256;
  int r;
  const float PI = 3.14159265;

  temp.createImage(nrows, ncols); // temp görüntü oluşturuldu

  for(rows = 0; rows < nrows; rows++){ //satır için
    for(cols = 0; cols < ncols; cols++){ //sütun için
      
      r = Image::getPix(rows, cols); //satır ve sütundaki piksel değerleri alındı

      temp(rows, cols) += (1/nrows) * abs(r * (cos(2 * PI * (1.0 * rows * cols / nrows)) - sin(2 * PI * (1.0 * rows * cols / nrows))) ) ; // IDFT formülü sin cos olarak uygulandı
      
    }
  }

  for(cols = 0; cols < ncols; cols++){ //sütun için
    for(rows = 0; rows < nrows; rows++){ //satır için
      
      r = Image::getPix(rows, cols); //satır ve sütundaki piksel değerleri alındı

      temp(rows, cols) += (1/ncols) * abs(r * (cos(2 * PI * (1.0 * rows * cols / ncols)) -  sin(2 * PI * (1.0 * rows * cols / ncols))) ) ; // IDFT formülü sin cos olarak uygulandı
      
    }
  }

return temp; //görüntü döndürüldü

}