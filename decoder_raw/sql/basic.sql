--
-- Basic tests
--

-- Create a replication slot
SELECT slotname FROM pg_create_logical_replication_slot('custom_slot', 'decoder_raw');

-- DEFAULT case
CREATE TABLE aa (a int primary key, b text);
INSERT INTO aa VALUES (1, 'aa'), (2, 'bb');
UPDATE aa SET b = 'cc' WHERE a = 1;
DELETE FROM aa WHERE a = 1;
SELECT data FROM pg_logical_slot_get_changes('custom_slot', NULL, NULL, 'include-transaction', 'on');
DROP TABLE aa;

-- FULL case
CREATE TABLE aa (a int primary key, b text);
ALTER TABLE aa REPLICA IDENTITY FULL;
INSERT INTO aa VALUES (1, 'aa'), (2, 'bb');
UPDATE aa SET b = 'cc' WHERE a = 1;
DELETE FROM aa WHERE a = 1;
SELECT data FROM pg_logical_slot_get_changes('custom_slot', NULL, NULL, 'include-transaction', 'on');
DROP TABLE aa;

-- NOTHING case
CREATE TABLE aa (a int primary key, b text);
ALTER TABLE aa REPLICA IDENTITY NOTHING;
INSERT INTO aa VALUES (1, 'aa'), (2, 'bb');
UPDATE aa SET b = 'cc' WHERE a = 1;
DELETE FROM aa WHERE a = 1;
SELECT data FROM pg_logical_slot_get_changes('custom_slot', NULL, NULL, 'include-transaction', 'on');
DROP TABLE aa;

-- Drop replication slot
SELECT pg_drop_replication_slot('custom_slot');
