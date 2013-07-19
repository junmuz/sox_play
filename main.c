#include <sox.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	
	if (argc != 2) {
		printf ("Incorrect Arguments\n");
		exit (-1);
	}
	

	int i, sox_status;
	/*	Sox File Descriptor	*/
	sox_format_t *sox_fd1, *sox_fd2;

	size_t sox_size = 1, sox_tsize = 0;

	sox_sample_t sox_buf[120];

	sox_signalinfo_t out_info;

	out_info.rate = 22050;
	out_info.channels = 1;
	out_info.precision = 16;
	out_info.length = SOX_IGNORE_LENGTH;
  	out_info.mult = 0;
	sox_uint64_t sox_off = 0;
//	sox_status = sox_seek (sox_fd1, sox_off, SOX_SEEK_SET);
	/*	Initialization of all format handlers	*/
	sox_format_init ();

	/*	Open Wav file for reading	*/
	sox_fd1 = sox_open_read (argv[1], NULL, NULL, "wav");
	sox_fd2 = sox_open_write ("default", &out_info, NULL, "alsa", NULL, sox_false);
	
	/*	Copy from one wav file to other	*/

	for (i = 0; i < 5; i++) {
		sox_fd1 = sox_open_read (argv[1], NULL, NULL, "wav");
		while (sox_size) {
			sox_size = sox_read (sox_fd1, sox_buf, 100);
			sox_write (sox_fd2, sox_buf, sox_size);
		}
		sox_size = 1;
		sox_close (sox_fd1);
	}

	/*	Close Wav file	*/
	sox_close (sox_fd1);
	sox_close (sox_fd2);

	/*	De-initialization of file format handlers	*/
	sox_format_quit ();
	return 0;
}
