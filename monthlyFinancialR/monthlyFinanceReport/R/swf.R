#' Extract SWF ata frame from SWF spreadsheet.
#'
#' Extract the SWF data frame from the SWF and fix the columns appropriately.
#'
#' @param swfFile The name of the file with the SWF spreadsheet
#' @return A data frame
#' @export
#'
#' @examples
#' \dontrun{
#' download_swf(422, "??", "??") %>% swf_df -> swfdf
#' }
swf_df <- function(excelFile) {
  coltypes <- c(rep('blank', 8), rep('text', 16), rep('numeric', 2), 'text', 'text', 'numeric',
                rep('text', 7), rep('numeric', 3), rep('text', 3), rep('numeric', 3), 'text',
                rep('numeric', 6), rep('text', 3), rep('blank', 15), rep('text', 10))
  readxl::read_excel(excelFile, 'Data', col_types = coltypes)
}

