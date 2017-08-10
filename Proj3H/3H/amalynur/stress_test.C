#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);



    /* ================================ */
    /* START STUDENT MODIFIABLE SECTION */
    /* ================================ */

    /* you may want one or more readers! */
    PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"
    
    Shrinker sr;
    Shrinker sr2;
    Shrinker sr3;
    LRConcat lr1;
    LRConcat lr2;
    LRConcat lr3;
    LRConcat lr4;
    LRConcat lr5;
    LRConcat lr6;
    TBConcat tb1;
    TBConcat tb2;
    TBConcat tb3;

    

    sr.SetInput(reader.GetOutput());
    sr2.SetInput(sr.GetOutput());
    sr3.SetInput(sr2.GetOutput());

    lr1.SetInput(sr3.GetOutput());
    lr1.SetInput2(sr3.GetOutput());
    lr2.SetInput(lr1.GetOutput());
    lr2.SetInput2(sr3.GetOutput());


    lr4.SetInput(lr2.GetOutput());
    lr4.SetInput2(sr3.GetOutput());
    lr5.SetInput(lr4.GetOutput());
    lr5.SetInput2(sr3.GetOutput());


    lr6.SetInput(sr3.GetOutput());
    lr6.SetInput2(lr5.GetOutput());
    
    tb2.SetInput(lr6.GetOutput());
    tb2.SetInput2(lr6.GetOutput());
    tb3.SetInput(tb2.GetOutput());
    tb3.SetInput2(tb2.GetOutput());


    


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb3.GetOutput();

    /* ================================ */
    /*  END STUDENT MODIFIABLE SECTION  */
    /* ================================ */



    try
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
