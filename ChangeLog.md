* 2014-07-21 0.5.1
   * Refactor `fmbuf`, make the api more user friendly
* 2014-05-29 0.4.10
   * Add `make doc` to generate api wiki
* 2014-05-24 0.4.9
   * Refactor fhash
* 2014-05-04 0.4.8
   * Refactor Makefile
   * exit non-zero when UT failure
* 2014-03-09 0.4.7
   * Fix the clock resolution higher than 1ms in some systems
* 2013-09-04 0.4.6
   * Fix the api name for fread_conf library
* 2013-09-04 0.4.5
   * Refine Makefile and README
* 2013-08-26 0.4.4
   * Fully support valgrind-check
   * Add timer service and integrate it into async_conn
* 2013-07-25 0.4.3
   * Add a sub folder for headers in include folder, which used for easy to maintain the headers
* 2013-07-25 0.4.2
   * Refine the return code of fpcap_convert
* 2013-07-25 0.4.1
   * Refine flist, remove the pl_mgr declare, instead of using flist*
   * Add a new api for flist -- flist_tail()
* 2013-07-24 0.4.0
   * Refine all filenames and api names
   * Refine all Makefiles
   * Support both 32 & 64 bit libs
* 2013-07-10 0.3.8
   * Refine flist's code
   * Fix coredump when open pcap file failed
* 2013-06-27 0.3.7
   * Add flist_sort api
   * Enhance the pcap lib, which expose tcp syn & ack flags
* 2013-03-28 0.3.6
   * Add pcap convertion feature
* 2013-03-12 0.3.5
   * Add hash set/get/del for uint64 api
* 2012-12-06 0.3.3
   * Issue #11 fix dead loop when no space on disk
* 2012-11-28 0.3.2
   * Add new interface -- fev_add_listener_byfd