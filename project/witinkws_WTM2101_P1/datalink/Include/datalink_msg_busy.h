/* vim: set fileencoding=utf-8:
 *
 *                   GNU GENERAL PUBLIC LICENSE
 *                       Version 2, June 1991
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 *
 */
#ifndef DATALINK_MSG_BUSY_H_2A0E98BE_2830_562C_C887_8DF6012C419D_INCLUDED_
#define DATALINK_MSG_BUSY_H_2A0E98BE_2830_562C_C887_8DF6012C419D_INCLUDED_

#define DATALINK_MSG_ID_BUSY        6

__PACKED_BEGIN
typedef struct __datalink_msg_busy_t {
    datalink_message_header_t   header;
    uint8_t                     dummy;
}__PACKED_END datalink_msg_busy_t;


#endif

