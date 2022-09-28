from twilio.rest import Client
import sys

# Your Account SID from twilio.com/console
account_sid = "AC57660bd0044d74f20255510a8403625e"
# Your Auth Token from twilio.com/console
auth_token  = "b8ad402433104aa1179fb2c0430180ef"

client = Client(account_sid, auth_token)

message = client.messages.create(
    to="+21623541410",
    # to=sys.argv[1],

    from_="+15737634755",
    body="your order is ready!")

print(message.sid)
