#ifndef IMAGE_H
#define IMAGE_H

class Source;

class Image
{
    private:
		unsigned char *data;
		int height;
		int width;
		Source* src;

	public:
		Image(void);
		Image(int width, int height);
		Image(Image &);
		void ResetSize(int width, int height);
		void SetSize(int width, int height);
		int get_w();
		int get_h();
		void setData(int width, int height);
		unsigned char* getData();
		virtual void Update();
		void SetSrc(Source *);
		~Image();

};

#endif