#ifndef CONSTANT_SB_H
#define CONSTANT_SB_H
//namespace forest
//{
    const int max_stars = 15000;		//  пока 15000, потом сделать максимально приближенной к 106 261
    const int max_spectral_channel_ = 3;	///< максимальное количество спектральных каналов
    const int max_frame_object_     = 512;	///< максимальное количество обнаруживаемых на кадре объектов
    const int max_wave_length_point_ = 1200;///< максимальное количество отсчетов длин волн
    const int max_OS_elements_point_ = 20;	///< максимальное количество элементов ОС
    const int max_angle_point_ = 360;		///< максимальное количество отсчетов углов

	const int maxNumTypeOb = 20;
	const int maxNumOb_ = 20;

    const double err_Angles_ = 1.0e-6;		///< допустимая ошибка представления углов, град
    const double err_WL_     = 1.0e-6;		///< допустимая ошибка представления длины волны, мкм
    const double eps_zero_   = 1.0e-8;		///< допустимая ошибка близости к нулю

	// phisics constants
	const double pi_  = 3.141592653589793;
	const double pi2_ = 2. * pi_;
	const double grad2radian_ = pi_ / 180.;
	const double radian2grad_ = 180. / pi_;
    const double h_  = 6.626068E-34;    ///< постоянная Планка, Дж/с
    const double c_  = 299792458;		///< скорость света, м/с
    const double kB_ = 1.3806504E-23;	///< постоянная Больцмана, Дж/К
    const double kSB_= 5.670367E-8;		///< постоянная Стефана-Больцмана, Вт/м4/К4
	
//}
#endif // CONSTANT_SB_H
