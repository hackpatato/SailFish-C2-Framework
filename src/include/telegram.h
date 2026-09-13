#ifndef TELEGRAM_H
#define TELEGRAM_H

int send_encrypted_log(const char *input_filepath, const char *bot_token, const char *chat_id, char key);

#endif