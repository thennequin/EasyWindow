
solution "EasyWindow"
	location				(_ACTION)
	language				"C++"
	configurations			{ "Debug", "Release" }
	platforms				{ "x32", "x64" }
	objdir					("../Intermediate/".._ACTION)
	flags					{ "StaticRuntime" }

	project "EasyWindowSample"
		uuid				"f3501d7f-3f2d-476b-b9e2-d6c629e327da"
		kind				"ConsoleApp"
		targetdir			"../Output/"

		files {
							"../**.cpp",
							"../**.h",
		}

		includedirs {
							".."
		}

		platforms{}

		configuration		"Debug"
			targetsuffix	"_d"
			flags			{ "Symbols" }
			
		configuration		"Release"
			targetsuffix	"_r"
			flags			{ "Optimize" }
