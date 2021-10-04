#include <stdio.h>
#include <stdlib.h>

#include "include/orca/discord.h"


void on_ready(
  struct discord *client,
  const struct discord_user *bot) {
  log_info("Bot conectado correctamente a Discord como %s#%s!",
      bot->username, bot->discriminator);
}

void on_ping(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg) {
  if(msg->author->bot) return; // ignorar bots

  struct discord_create_message_params params = { .content = "pong" };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_pong(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg) {
  if(msg->author->bot) return; // ignorar bots

  struct discord_create_message_params params = { .content = "ping" };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

int main() {
  struct discord *client = discord_init(getenv("UNSABOTC_TOKEN"));

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "ping", &on_ping);
  discord_set_on_command(client, "pong", &on_pong);

  discord_run(client);

  discord_cleanup(client);

  return 0;
}
