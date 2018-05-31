#include <iostream>  
#include <exiv2/exiv2.hpp>  
#pragma comment(lib,"libexiv2.lib")  
#pragma comment(lib,"xmpsdk.lib")  
#pragma comment(lib,"libexpat.lib")  
#pragma comment(lib,"zlib1.lib")  

//查找一个ExifKey避免没有的Key产生段错误
std::string FindExifKey(Exiv2::ExifData &ed, std::string key) {
	Exiv2::ExifKey tmp = Exiv2::ExifKey(key);
	Exiv2::ExifData::iterator pos = ed.findKey(tmp);
	if (pos == ed.end()) {
		return "Unknow";
	}
	return pos->value().toString();
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "Need a File.";
		return 0;
	}

	//判断文件是否有效  
	if (!Exiv2::fileExists(argv[1], true)) {
		std::cout << "File Path Error." << std::endl;
		return -1;
	}

	//获取文件大小
	FILE *FP = fopen(argv[1], "rb");
	fseek(FP, 0, SEEK_END);			//定位到文件末 
	int FileSize = ftell(FP);       //文件长度
	fclose(FP);

	Exiv2::Image::AutoPtr &image = Exiv2::ImageFactory::open(argv[1]);
	if (image.get() == 0)
	{
		std::cout << "Read Exif Error." << std::endl;
		return -2;
	}

	//读取照片的exif信息  
	image->readMetadata();
	Exiv2::ExifData ed = image->exifData();//得到exif信息  

	if (ed.empty())
	{
		std::cout << "Not Find ExifInfo" << std::endl;
		return -2;
	}
	
	std::cout << "文件名称	:" << argv[1] << std::endl;
	std::cout << "文件大小	:" << FileSize << std::endl;
	std::cout << "版权		:" << FindExifKey(ed, "Exif.Image.Copyright") << std::endl;
	std::cout << "创作人		:" << FindExifKey(ed, "Exif.Image.Artist") << std::endl;
	std::cout << "相机品牌	:" << FindExifKey(ed, "Exif.Image.Make") << std::endl;
	std::cout << "相机型号	:" << FindExifKey(ed, "Exif.Image.Model") << std::endl;
	std::cout << "镜头型号	:" << FindExifKey(ed, "Exif.Photo.LensModel") << std::endl;
	std::cout << "镜头序列号	:" << FindExifKey(ed, "Exif.Photo.LensSerialNumber") << std::endl;
	std::cout << "ISO		:" << FindExifKey(ed, "Exif.Photo.ISOSpeedRatings") << std::endl;
	std::cout << "光圈		:" << FindExifKey(ed, "Exif.Photo.FNumber") << std::endl;
	std::cout << "焦距		:" << FindExifKey(ed, "Exif.Photo.FocalLength") << std::endl;
	std::cout << "快门		:" << FindExifKey(ed, "Exif.Photo.ExposureTime") << std::endl;
	std::cout << "拍摄时间	:" << FindExifKey(ed, "Exif.Image.DateTime") << std::endl;
	std::cout << "闪光灯		:" << FindExifKey(ed, "Exif.CanonCs.FlashMode") << std::endl;
	std::cout << "水平分辨率	:" << FindExifKey(ed, "Exif.Image.XResolution") << std::endl;
	std::cout << "垂直分辨率	:" << FindExifKey(ed, "Exif.Image.YResolution") << std::endl;
	std::cout << "照片尺寸	:" << FindExifKey(ed, "Exif.Photo.PixelYDimension") << " x " << FindExifKey(ed, "Exif.Photo.PixelXDimension") << std::endl;

	std::cout << "\n下面是原始信息:\n" << std::endl;
	for (Exiv2::ExifData::iterator tmp = ed.begin(); tmp != ed.end(); tmp++) {  
	  std::cout << tmp->tagName() << " (" << tmp->key() << ")       " << tmp->value() <<std::endl;
	}
	return 0;
}