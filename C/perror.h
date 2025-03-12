void handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}
