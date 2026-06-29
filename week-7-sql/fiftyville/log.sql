-- Keep a log of any SQL queries you execute as you solve the mystery.

-- We know that the theft took place on July 28 2025 at Humphrey Street
SELECT * FROM crime_scene_reports WHERE year = '2025' AND month = '07' AND day = '28' AND street = 'Humphrey Street';
SELECT description FROM crime_scene_reports WHERE year = '2025' AND month = '07' AND day = '28' AND street = 'Humphrey Street';
-- Found:
-- ----------------------------------------------------------------+
-- |                                                                                                       description                                                                                                        |
-- +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


-- We now know that we have 3 witnesses and their transcipts are available in interviews table.
SELECT * FROM interviews WHERE year = '2025' and month = '7' and day = '28' and (transcript like '%thief%' or transcript like '%theft%');
SELECT name, transcript FROM interviews WHERE year = '2025' and month = '7' and day = '28' and (transcript like '%thief%' or transcript like '%theft%');
-- Found:
-- +---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- |  name   |                                                                                                                                                     transcript                                                                                                                                                      |
-- +---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- +---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


-- As per the leads from Witness 1, Ruth
SELECT * FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10' and minute between '15' and '25';
-- Found:
-- There are 8 vehicles exited from the bakery parking lot.

-- Recognized license plates:
SELECT license_plate FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10' and minute between '15' and '25';
-- +---------------+
-- | license_plate |
-- +---------------+
-- | 5P2BI95       |
-- | 94KL13X       |
-- | 6P58WS2       |
-- | 4328GD8       |
-- | G412CB7       |
-- | L93JTIZ       |
-- | 322W7JE       |
-- | 0NTHK55       |
-- +---------------+


-- Using above query as a sub query in the people table
SELECT id, name, phone_number, passport_number, license_plate FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10' and minute between '15' and '25');
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+


-- As per witness 2
SELECT * FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28' AND atm_location = 'Leggett Street' and transaction_type = 'withdraw';
-- Found:
-- There are 8 withdrawals:
SELECT account_number, amount FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28' AND atm_location = 'Leggett Street' and transaction_type = 'withdraw';
-- +----------------+--------+
-- | account_number | amount |
-- +----------------+--------+
-- | 28500762       | 48     |
-- | 28296815       | 20     |
-- | 76054385       | 60     |
-- | 49610011       | 50     |
-- | 16153065       | 80     |
-- | 25506511       | 20     |
-- | 81061156       | 30     |
-- | 26013199       | 35     |
-- +----------------+--------+


-- Using the account numbers, searching in bank_accounts
SELECT person_id, name FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28' AND atm_location = 'Leggett Street' and transaction_type = 'withdraw');
-- +-----------+
-- | person_id |
-- +-----------+
-- | 686048    |
-- | 514354    |
-- | 458378    |
-- | 395717    |
-- | 396669    |
-- | 467400    |
-- | 449774    |
-- | 438727    |
-- +-----------+


-- Let's find the matching people ids from both witness 1 analysis and witness 2 analysis
SELECT people.id, people.name, people.passport_number, people.phone_number FROM people JOIN
(SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28'
    AND atm_location = 'Leggett Street' and transaction_type = 'withdraw')) Witness1
ON people.id = Witness1.person_id
JOIN
(SELECT id FROM people WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10'
    and minute between '15' and '25')) Witness2
ON people.id = Witness2.id;
-- +--------+-------+-----------------+----------------+
-- |   id   | name  | passport_number |  phone_number  |
-- +--------+-------+-----------------+----------------+
-- | 686048 | Bruce | 5773159633      | (367) 555-5533 |
-- | 514354 | Diana | 3592750733      | (770) 555-1861 |
-- | 396669 | Iman  | 7049073643      | (829) 555-5269 |
-- | 467400 | Luca  | 8496433585      | (389) 555-5198 |
-- +--------+-------+-----------------+----------------+


-- Finding the caller according to 3rd witness and using the information we already found from witness 1 and witness 2
SELECT p1.name as caller_name, caller as caller_phone_number,
p2.name as receiver_name, receiver as receiver_phone_number,
duration FROM phone_calls
JOIN people p1 ON phone_calls.caller = p1.phone_number
JOIN people p2 ON phone_calls.receiver = p2.phone_number
WHERE caller IN
(SELECT people.phone_number FROM people JOIN
    (SELECT person_id FROM bank_accounts WHERE account_number IN (
        SELECT account_number FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28'
        AND atm_location = 'Leggett Street' and transaction_type = 'withdraw')) Witness1
    ON people.id = Witness1.person_id
    JOIN
    (SELECT id FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10'
        and minute between '15' and '25')) Witness2
    ON people.id = Witness2.id) AND duration < 60;
-- +-------------+---------------------+---------------+-----------------------+----------+
-- | caller_name | caller_phone_number | receiver_name | receiver_phone_number | duration |
-- +-------------+---------------------+---------------+-----------------------+----------+
-- | Bruce       | (367) 555-5533      | Robin         | (375) 555-8161        | 45       |
-- | Diana       | (770) 555-1861      | Philip        | (725) 555-3243        | 49       |
-- | Bruce       | (367) 555-5533      | Charlotte     | (455) 555-5315        | 31       |
-- +-------------+---------------------+---------------+-----------------------+----------+


-- Finding passport numbers using the same query but selecting passport_number
SELECT people.name, people.passport_number, people.phone_number FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE caller IN
    (SELECT people.phone_number FROM people JOIN
        (SELECT person_id FROM bank_accounts WHERE account_number IN (
            SELECT account_number FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28'
            AND atm_location = 'Leggett Street' and transaction_type = 'withdraw')) Witness1
        ON people.id = Witness1.person_id
        JOIN
        (SELECT id FROM people WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10'
            and minute between '15' and '25')) Witness2
        ON people.id = Witness2.id) AND duration < 60);
-- +-------+-----------------+----------------+
-- | name  | passport_number |  phone_number  |
-- +-------+-----------------+----------------+
-- | Diana | 3592750733      | (770) 555-1861 |
-- | Bruce | 5773159633      | (367) 555-5533 |
-- +-------+-----------------+----------------+


-- Using the passport numbers, we can find the flight, seat no., destination
SELECT a.abbreviation, a.full_name, a.city,
        p.seat,
        f.year, f.month, f.day, f.hour, f.minute,
        pe.name, pe.passport_number, pe.phone_number
        FROM flights AS f JOIN airports AS a
        ON f.destination_airport_id = a.id
        JOIN passengers AS p ON p.flight_id = f.id
        JOIN people AS pe ON pe.passport_number = p.passport_number
        WHERE f.year = '2025' AND f.month = '7' AND f.day = '29'
        AND pe.passport_number IN (
            SELECT people.passport_number FROM people WHERE phone_number IN (
                SELECT caller FROM phone_calls WHERE caller IN
                (SELECT people.phone_number FROM people JOIN
                    (SELECT person_id FROM bank_accounts WHERE account_number IN (
                        SELECT account_number FROM atm_transactions WHERE year = '2025' AND month = '7' AND day = '28'
                        AND atm_location = 'Leggett Street' and transaction_type = 'withdraw')) Witness1
                    ON people.id = Witness1.person_id
                    JOIN
                    (SELECT id FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year = '2025' and month = '7' and day = '28' and hour = '10'
                        and minute between '15' and '25')) Witness2
                    ON people.id = Witness2.id) AND duration < 60)
        );

-- +--------------+-----------------------------+---------------+------+------+-------+-----+------+--------+-------+-----------------+----------------+
-- | abbreviation |          full_name          |     city      | seat | year | month | day | hour | minute | name  | passport_number |  phone_number  |
-- +--------------+-----------------------------+---------------+------+------+-------+-----+------+--------+-------+-----------------+----------------+
-- | BOS          | Logan International Airport | Boston        | 4C   | 2025 | 7     | 29  | 16   | 0      | Diana | 3592750733      | (770) 555-1861 |
-- | LGA          | LaGuardia Airport           | New York City | 4A   | 2025 | 7     | 29  | 8    | 20     | Bruce | 5773159633      | (367) 555-5533 |
-- +--------------+-----------------------------+---------------+------+------+-------+-----+------+--------+-------+-----------------+----------------+

-- Thief is Bruce who catched the earliest flight at 8 20 AM

