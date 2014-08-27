#include "Gvar.h"
#include "selFloat.h"

#include <assert.h>  // required on comet-10; gcc --version => 3.3.5

// this function reverses the bytes of a datum
static void reverse_bytes(void* datum, unsigned len) {       
	char* bin = (char*) datum;
	char bout[1024];
	assert( len < sizeof(bout) );
	for ( unsigned i = 0; i < len; i++ ) {
		bout[i] = bin[len - i - 1];
	}
	memcpy(datum, bout, len);
}


float gvarfloat2float(float gvf) {
    reverse_bytes(&gvf, sizeof(float));
    SelFloat sf(gvf);
    return float(sf);
}

 
int recIndexFloat( int i ) {

   if ( (i >= 4 && i <= 10)  ||  (i >= 13 && i <= 60) )
	return 1;

   int j;
   for (j=0; j<5; j++) {

        if ( (i >= (61 + 55*j) && i <= (63 + 55*j))   ||  
             (i >= (65 + 55*j) && i <= (94 + 55*j))   || 
             (i >= (98 + 55*j) && i <= (100 + 55*j))  ||  
	     (i >= (103 + 55*j) && i <= (105 + 55*j)) || 
             (i >= (108 + 55*j) && i <= (110 + 55*j)) ||  
 	     (i >= (113 + 55*j) && i <= (115 + 55*j))  ) {
      	   return 1;
   	}
   }
	
   return 0;

}


namespace Gvar {
  Block0Doc::Block0Doc(Block *block){
    this->block = block ;
    uint8_t* data = block->getRawData () ;

    Spcid = data[0] ;
    Spsid = data[1] ;

    // iscan by Jie
//    for (int i=2; i<6; i++) {
//    }

    // ISCAN Iscan;/* 3 6 */
    Iscan = *((uint32_t*)&data[2]);	

    imc = (Iscan & 0x00800000) == 0x00800000; 
    flipflag = (Iscan & 0x00008000) == 0x00008000;


    Idsub = data[6] ;

    for (int i=7; i<14; i++) {
      IdsubIR[i-7] = data[i] ;
    }

    // ignore time for now, jiezhang ???
    Tcurr.setTime (&data[22]) ;
    Tched.setTime (&data[30]) ;
    Tctrl.setTime (&data[38]) ;
    Tlhed.setTime (&data[46]) ;
    Tltrl.setTime (&data[54]) ;
    Tipfs.setTime (&data[62]) ;
    Tinfs.setTime (&data[70]) ;
    Tispc.setTime (&data[78]) ;
    Tiecl.setTime (&data[86]) ;
    Tibbc.setTime (&data[94]) ;
    Tistr.setTime (&data[102]) ;
    Tlran.setTime (&data[110]) ;
    Tiirt.setTime (&data[118]) ;
    Tivit.setTime (&data[126]) ;
    Tclmt.setTime (&data[134]) ;
    Tiona.setTime (&data[142]) ;

    Risct = ((uint16_t)(data[150] << 8)) + ((uint16_t)data[151]) ;
    Aisct = ((uint16_t)(data[152] << 8)) + ((uint16_t)data[153]) ;
    Insln = ((uint16_t)(data[154] << 8)) + ((uint16_t)data[155]) ;

    // get Iwfpx, Iefpx, Infln, Isfln
    Iwfpx = ((uint16_t)(data[156] << 8)) + ((uint16_t)data[157]) ;
    Iefpx = ((uint16_t)(data[158] << 8)) + ((uint16_t)data[159]) ;
    Infln = ((uint16_t)(data[160] << 8)) + ((uint16_t)data[161]) ;
    Isfln = ((uint16_t)(data[162] << 8)) + ((uint16_t)data[163]) ;

    Impdx = ((uint16_t)(data[164] << 8)) + ((uint16_t)data[165]) ;

    Subla = gvarfloat2float( *((float*)&data[174]) );
    Sublo = gvarfloat2float( *((float*)&data[178]) );

     Ifnw1 = gvarfloat2float( *((float*)&data[230]) ); /*231 234*/
     Ifnw2 = gvarfloat2float( *((float*)&data[234]) ); /*235 238*/
     Ifse1 = gvarfloat2float( *((float*)&data[238]) ); /*239 242*/
     Ifse2 = gvarfloat2float( *((float*)&data[242]) ); /*243 246*/


    // get Ifram
    //cout <<" Ifram 1: " << data[228] <<endl;
    Ifram = data[228] ; /*229*/
    //cout <<" Ifram 2: " << (int)Ifram <<endl;

    for (int imcNo=0; imcNo<4; imcNo++) {
      Imc_identifier[imcNo] = data[278+imcNo];
    }

    //parsed by Haiyan Yang
    memcpy(rec, &data[278], 336*sizeof(float));
    for ( int i = 0; i < 336; i++ ) {
	// we first resever bytes for all members:
	reverse_bytes(&rec[i], sizeof(float));
	
	int isfloatIndex = recIndexFloat(i); 
	
	// then we make conversion only for floating point numbers:
	  if (isfloatIndex) { 
		SelFloat sf(rec[i]);
		rec[i] = float(sf);
	}
    }

    
    /** Convert Epoch from cda to IEEE int format 
     *  and store into rec
     */
    EpochDate.setTime (&data[322]) ;
    int epochIEEE[2];
    EpochDate.toIEEE(epochIEEE);
    memcpy(&rec[11], epochIEEE, 2*sizeof(int));

  
    /* In November 2009, these locations where changed see 'Copying
       the Instrument Nadir and Detector Offsets from Block 11 to
       Block 0 for GOES O and Beyond', A White Paper Prepared by SGT
       for the Office of Satellite Operations, 9/21/2009
       http://www.osd.noaa.gov/GVAR_Downloads/documents/GOES-O-GVAR_Change.pdf
    */
    Iofnc = data[8032]; /* 8033-8033 F_IOFNC */
    Iofec = data[8033]; /* 8034-8034 F_IOFEC */
    /* 8035-8036 F_IOFNI   8037-8038 F_IOFEI */
    Iofni = ((uint16_t)(data[8034] << 8)) + ((uint16_t)data[8035]); 
    Iofei = ((uint16_t)(data[8036] << 8)) + ((uint16_t)data[8037]);

  }//Block0Doc


  // added by Haiyan uint8_t rec[336*4]; /* 279 1626*/

	const float* Block0Doc::getRec() {
		return rec;
	}

        uint8_t Block0Doc::getIofnc() { 
		return Iofnc;
	}
        uint8_t Block0Doc::getIofec() {
		return Iofec;
	}
        uint16_t Block0Doc::getIofni() {
		return Iofni;
	}
        uint16_t Block0Doc::getIofei() {
		return Iofei;
	}

	int Block0Doc::getImc(){
		return imc;
	}

	int Block0Doc::getFlipflag(){
	    if (flipflag)	
		return 1;	
	    else 
		return -1;
	}

        CdaTime* Block0Doc::getEpochDate() {
	  return &EpochDate;
	} /* 323 330*/


  CdaTime* Block0Doc::getCurrentTime() 
  {
    return &Tcurr;
  }//getCurrentTime()


  void Block0Doc::block0time(ostream & out ){
    out <<Risct<<"\t"<<Tcurr<<"\t"<<Tched<<"\t"<<Tctrl<<"\t"<<Tlhed<<"\t"
        <<Tltrl<<"\t"<<Tipfs<<"\t"<<Tinfs<<"\t"<<Tispc<<"\t"
        <<Tiecl<<"\t"<<Tibbc<<"\t"<<Tistr<<"\t"<<Tlran<<"\t"
	<<Tiirt<<"\t"<<Tivit<<"\t"<<Tclmt<<"\t"<<Tiona;
  }

  void Block0Doc::block0timeText(ostream & out){
    out<<"Risct\t";
    out<<"Tcurr-y\tTcurr-d\tTcurr-h\tTcurr-m\tTcurr-s\tTcurr-ms\tTcurr-f\t";
    out<<"Tched-y\tTched-d\tTched-h\tTched-m\tTched-s\tTched-ms\tTched-f\t";
    out<<"Tctrl-y\tTctrl-d\tTctrl-h\tTctrl-m\tTctrl-s\tTctrl-ms\tTctrl-f\t";
    out<<"Tlhed-y\tTlhed-d\tTlhed-h\tTlhed-m\tTlhed-s\tTlhed-ms\tTlhed-f\t";

    out<<"Tltrl-y\tTltrl-d\tTltrl-h\tTltrl-m\tTltrl-s\tTltrl-ms\tTltrl-f\t";
    out<<"Tipfs-y\tTipfs-d\tTipfs-h\tTipfs-m\tTipfs-s\tTipfs-ms\tTipfs-f\t";
    out<<"Tinfs-y\tTinfs-d\tTinfs-h\tTinfs-m\tTinfs-s\tTinfs-ms\tTinfs-f\t";
    out<<"Tispc-y\tTispc-d\tTispc-h\tTispc-m\tTispc-s\tTispc-ms\tTispc-f\t";

    out<<"Tiecl-y\tTiecl-d\tTiecl-h\tTiecl-m\tTiecl-s\tTiecl-ms\tTiecl-f\t";
    out<<"Tibbc-y\tTibbc-d\tTibbc-h\tTibbc-m\tTibbc-s\tTibbc-ms\tTibbc-f\t";
    out<<"Tistr-y\tTistr-d\tTistr-h\tTistr-m\tTistr-s\tTistr-ms\tTistr-f\t";
    out<<"Tlran-y\tTlran-d\tTlran-h\tTlran-m\tTlran-s\tTlran-ms\tTlran-f\t";

    out<<"Tiirt-y\tTiirt-d\tTiirt-h\tTiirt-m\tTiirt-s\tTiirt-ms\tTiirt-f\t";
    out<<"Tivit-y\tTivit-d\tTivit-h\tTivit-m\tTivit-s\tTivit-ms\tTivit-f\t";
    out<<"Tclmt-y\tTclmt-d\tTclmt-h\tTclmt-m\tTclmt-s\tTclmt-ms\tTclmt-f\t";
    out<<"Tiona-y\tTiona-d\tTiona-h\tTiona-m\tTiona-s\tTiona-ms\tTiona-f";
  }

  void Block0Doc::getImcIdentifier (char* imcIdentifier) {
    memcpy (imcIdentifier, Imc_identifier, 4) ;
  }

  void Block0Doc::print(ostream & out){
    out << "    spcid:"<<spcid();
    out << "    frame:"<<frame();
    out << "    RISCT:"<<rScanCount();
    out << "    AISCT:"<<aScanCount();
    out << "    INSLN:"<<nsln()<<"\n";
    out << "    IOFNC:"<<getIofnc()<<" IOFEC:"<<getIofec()<<" IOFNI:"<<getIofni()<< " IOFEI:"<<getIofei()<<"\n";
    out << "    SUBLA:"<<getSubla()<<" SUBLO:"<<getSublo()<<"\n";

    out<< boost::format
      ("    imcIdentifier:%s\n") % getImc();
    out<< boost::format
      ("    nln:%5d\n    epx:%5d   wpx:%5d\n    sln:%5d\n") 
      % nln() % wpx() % epx() % sln();
  }
  
}//namespace Gvar
