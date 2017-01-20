#' Download SWF Spreadsheet from CS-DocDB.
#'
#' Download the SWF spreadsheet from CS-doc-3799
#' \url{http://cd-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3799}. You must
#' supply the version number you want (no default) and the access username and
#' password for DocDB. A temporary file is created and that name is returned.
#'
#' @param ver The version of CS-doc-3799
#' @param username The username you use for cd-docdb
#' @param passwd The password you use for cd-docdb
#' @return The name of the temporary file
#' @export
download_swf <- function(ver, username, passwd) {
  baseurl <- 'http://cd-docdb.fnal.gov:8080/cgi-bin/RetrieveFile?docid=3799&filename=Effort%20YTD%20Dec%20011117%20%28RC%29.xlsx&version='
  url <- paste(baseurl, ver, sep="")
  tmp <- tempfile(fileext = '.xlsx')
  httr::GET(url, httr::write_disk(tmp), httr::authenticate(username, passwd))
  tmp
}

