#include <gtest/gtest.h>
#include "../../../src/utils/log.hpp"
#include "../../../src/general.hpp"
#include "../../../src/conf/Filetypes.hpp"

TEST(FiletypesTest, Constructor)
{
	bool status = false;
	//	Using pointer new + delete to asure 0 leaks (smart pointers)
	ft::Filetypes*	types = new ft::Filetypes(&status);
    EXPECT_EQ(status, true);
	delete types;
}

TEST(FiletypesTest, types)
{
	//	Using pointer new + delete to asure 0 leaks (smart pointers)
	ft::Filetypes*	types = new ft::Filetypes(NULL);
    EXPECT_EQ(types->get("html"), "text/html");
	EXPECT_EQ(types->get("htm"), "text/html");
	EXPECT_EQ(types->get("shtml"), "text/html");
	EXPECT_EQ(types->get("css"), "text/css");
	EXPECT_EQ(types->get("xml"), "text/xml");
	EXPECT_EQ(types->get("rss"), "text/xml");
	EXPECT_EQ(types->get("gif"), "image/gif");
	EXPECT_EQ(types->get("jpeg"), "image/jpeg");
	EXPECT_EQ(types->get("jpg"), "image/jpeg");
	EXPECT_EQ(types->get("js"), "application/x-javascript");
	EXPECT_EQ(types->get("txt"), "text/plain");
	EXPECT_EQ(types->get("htc"), "text/x-component");
	EXPECT_EQ(types->get("mml"), "text/mathml");
	EXPECT_EQ(types->get("png"), "image/png");
	EXPECT_EQ(types->get("ico"), "image/x-icon");
	EXPECT_EQ(types->get("jng"), "image/x-jng");
	EXPECT_EQ(types->get("wbmp"), "image/vnd.wap.wbmp");
	EXPECT_EQ(types->get("jar"), "application/java-archive");
	EXPECT_EQ(types->get("war"), "application/java-archive");
	EXPECT_EQ(types->get("ear"), "application/java-archive");
	EXPECT_EQ(types->get("hqx"), "application/mac-binhex40");
	EXPECT_EQ(types->get("pdf"), "application/pdf");
	EXPECT_EQ(types->get("cco"), "application/x-cocoa");
	EXPECT_EQ(types->get("jardiff"), "application/x-java-archive-diff");
	EXPECT_EQ(types->get("jnlp"), "application/x-java-jnlp-file");
	EXPECT_EQ(types->get("run"), "application/x-makeself");
	EXPECT_EQ(types->get("pl"), "application/x-perl");
	EXPECT_EQ(types->get("pm"), "application/x-perl");
	EXPECT_EQ(types->get("prc"), "application/x-pilot");
	EXPECT_EQ(types->get("pdb"), "application/x-pilot");
	EXPECT_EQ(types->get("rar"), "application/x-rar-compressed");
	EXPECT_EQ(types->get("rpm"), "application/x-redhat-package-manager");
	EXPECT_EQ(types->get("sea"), "application/x-sea");
	EXPECT_EQ(types->get("swf"), "application/x-shockwave-flash");
	EXPECT_EQ(types->get("sit"), "application/x-stuffit");
	EXPECT_EQ(types->get("tcl"), "application/x-tcl");
	EXPECT_EQ(types->get("tk"), "application/x-tcl");
	EXPECT_EQ(types->get("der"), "application/x-x509-ca-cert");
	EXPECT_EQ(types->get("pem"), "application/x-x509-ca-cert");
	EXPECT_EQ(types->get("crt"), "application/x-x509-ca-cert");
	EXPECT_EQ(types->get("xpi"), "application/x-xpinstall");
	EXPECT_EQ(types->get("zip"), "application/zip");
	EXPECT_EQ(types->get("deb"), "application/octet-stream");
	EXPECT_EQ(types->get("bin"), "application/octet-stream");
	EXPECT_EQ(types->get("exe"), "application/octet-stream");
	EXPECT_EQ(types->get("dll"), "application/octet-stream");
	EXPECT_EQ(types->get("dmg"), "application/octet-stream");
	EXPECT_EQ(types->get("eot"), "application/octet-stream");
	EXPECT_EQ(types->get("iso"), "application/octet-stream");
	EXPECT_EQ(types->get("img"), "application/octet-stream");
	EXPECT_EQ(types->get("msi"), "application/octet-stream");
	EXPECT_EQ(types->get("msp"), "application/octet-stream");
	EXPECT_EQ(types->get("msm"), "application/octet-stream");
	EXPECT_EQ(types->get("mp3"), "audio/mpeg");
	EXPECT_EQ(types->get("ra"), "audio/x-realaudio");
	EXPECT_EQ(types->get("mpeg"), "video/mpeg");
	EXPECT_EQ(types->get("mpg"), "video/mpeg");
	EXPECT_EQ(types->get("mov"), "video/quicktime");
	EXPECT_EQ(types->get("flv"), "video/x-flv");
	EXPECT_EQ(types->get("avi"), "video/x-msvideo");
	EXPECT_EQ(types->get("wmv"), "video/x-ms-wmv");
	EXPECT_EQ(types->get("asx"), "video/x-ms-asf");
	EXPECT_EQ(types->get("asf"), "video/x-ms-asf");
	EXPECT_EQ(types->get("mng"), "video/x-mng");
	delete types;
}


