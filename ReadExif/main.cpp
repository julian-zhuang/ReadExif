#include <iostream>  
#include <exiv2/exiv2.hpp>  
#pragma comment(lib,"libexiv2.lib")  
#pragma comment(lib,"xmpsdk.lib")  
#pragma comment(lib,"libexpat.lib")  
#pragma comment(lib,"zlib1.lib")  

//����һ��ExifKey����û�е�Key�����δ���
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

	//�ж��ļ��Ƿ���Ч  
	if (!Exiv2::fileExists(argv[1], true)) {
		std::cout << "File Path Error." << std::endl;
		return -1;
	}

	//��ȡ�ļ���С
	FILE *FP = fopen(argv[1], "rb");
	fseek(FP, 0, SEEK_END);			//��λ���ļ�ĩ 
	int FileSize = ftell(FP);       //�ļ�����
	fclose(FP);

	Exiv2::Image::AutoPtr &image = Exiv2::ImageFactory::open(argv[1]);
	if (image.get() == 0)
	{
		std::cout << "Read Exif Error." << std::endl;
		return -2;
	}

	//��ȡ��Ƭ��exif��Ϣ  
	image->readMetadata();
	Exiv2::ExifData ed = image->exifData();//�õ�exif��Ϣ  

	if (ed.empty())
	{
		std::cout << "Not Find ExifInfo" << std::endl;
		return -2;
	}
	
	std::cout << "�ļ�����	:" << argv[1] << std::endl;
	std::cout << "�ļ���С	:" << FileSize << std::endl;
	std::cout << "��Ȩ		:" << FindExifKey(ed, "Exif.Image.Copyright") << std::endl;
	std::cout << "������		:" << FindExifKey(ed, "Exif.Image.Artist") << std::endl;
	std::cout << "���Ʒ��	:" << FindExifKey(ed, "Exif.Image.Make") << std::endl;
	std::cout << "����ͺ�	:" << FindExifKey(ed, "Exif.Image.Model") << std::endl;
	std::cout << "��ͷ�ͺ�	:" << FindExifKey(ed, "Exif.Photo.LensModel") << std::endl;
	std::cout << "��ͷ���к�	:" << FindExifKey(ed, "Exif.Photo.LensSerialNumber") << std::endl;
	std::cout << "ISO		:" << FindExifKey(ed, "Exif.Photo.ISOSpeedRatings") << std::endl;
	std::cout << "��Ȧ		:" << FindExifKey(ed, "Exif.Photo.FNumber") << std::endl;
	std::cout << "����		:" << FindExifKey(ed, "Exif.Photo.FocalLength") << std::endl;
	std::cout << "����		:" << FindExifKey(ed, "Exif.Photo.ExposureTime") << std::endl;
	std::cout << "����ʱ��	:" << FindExifKey(ed, "Exif.Image.DateTime") << std::endl;
	std::cout << "�����		:" << FindExifKey(ed, "Exif.CanonCs.FlashMode") << std::endl;
	std::cout << "ˮƽ�ֱ���	:" << FindExifKey(ed, "Exif.Image.XResolution") << std::endl;
	std::cout << "��ֱ�ֱ���	:" << FindExifKey(ed, "Exif.Image.YResolution") << std::endl;
	std::cout << "��Ƭ�ߴ�	:" << FindExifKey(ed, "Exif.Photo.PixelYDimension") << " x " << FindExifKey(ed, "Exif.Photo.PixelXDimension") << std::endl;

	std::cout << "\n������ԭʼ��Ϣ:\n" << std::endl;
	for (Exiv2::ExifData::iterator tmp = ed.begin(); tmp != ed.end(); tmp++) {  
	  std::cout << tmp->tagName() << " (" << tmp->key() << ")       " << tmp->value() <<std::endl;
	}
	return 0;
}