void PFATAL(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void PERROR_CONT(const char* msg)
{
  perror(msg);
  continue;
}
