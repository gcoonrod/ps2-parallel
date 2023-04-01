void init_PS2A(void);
void init_dbug(void);
void ps2_read(void);
void ps2_buf_push(unsigned char c);
unsigned char ps2_buf_pull(void);
void ps2_buf_empty(void);